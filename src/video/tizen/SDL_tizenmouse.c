/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>
  Copyright 2015 Samsung Electronics co., Ltd. All Rights Reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "../../SDL_internal.h"
#include "../../events/SDL_mouse_c.h"

#include "SDL_tizenmouse.h"
#include "SDL_log.h"

#include <sys/mman.h>
#include <fcntl.h>


typedef struct {
    struct wl_buffer   *buffer;
    struct wl_surface  *surface;
    SDL_WindowData     *win_data;

    int                hot_x, hot_y;
    int                w, h;

    /* Either a preloaded cursor, or one we created ourselves */
    struct wl_cursor   *cursor;
    void               *shm_data;
} Tizen_CursorData;

static int
wayland_create_tmp_file(off_t size)
{
    static const char template[] = "/sdl-shared-XXXXXX";
    char *xdg_path;
    char tmp_path[PATH_MAX];
    int fd;

    xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
    if (!xdg_path) {
        errno = ENOENT;
        return -1;
    }

    SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
    SDL_strlcat(tmp_path, template, PATH_MAX);

    fd = mkostemp(tmp_path, O_CLOEXEC);
    if (fd < 0)
        return -1;

    if (ftruncate(fd, size) < 0) {
        close(fd);
        return -1;
    }

    return fd;
}

static void
mouse_buffer_release(void *data, struct wl_buffer *buffer)
{
}

static const struct wl_buffer_listener mouse_buffer_listener = {
    mouse_buffer_release
};

static int
create_buffer_from_shm(Tizen_CursorData *d, int width, int height, uint32_t format)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = (SDL_VideoData *) vd->driverdata;
    struct wl_shm_pool *shm_pool;

    int stride = width * 4;
    int size = stride * height;

    int shm_fd;

    shm_fd = wayland_create_tmp_file(size);
    if (shm_fd < 0)
    {
        fprintf(stderr, "creating mouse cursor buffer failed!\n");
        return -1;
    }

    d->shm_data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (d->shm_data == MAP_FAILED) {
        d->shm_data = NULL;
        fprintf (stderr, "mmap () failed\n");
        close (shm_fd);
    }

    shm_pool = wl_shm_create_pool(ecore_wl_shm_get(), shm_fd, size);
    d->buffer = wl_shm_pool_create_buffer(shm_pool, 0, width, height, stride, format);
    wl_buffer_add_listener(d->buffer, &mouse_buffer_listener, d);

    wl_shm_pool_destroy (shm_pool);
    close (shm_fd);

    return 0;
}

static SDL_Cursor *
Tizen_CreateCursor(SDL_Surface *surface, int hot_x, int hot_y)
{
    SDL_Cursor *cursor;

    cursor = calloc(1, sizeof (*cursor));
    if (cursor) {
        SDL_VideoDevice *vd = SDL_GetVideoDevice ();
        SDL_Window* window = vd->windows;

        Tizen_CursorData *data = calloc (1, sizeof (Tizen_CursorData));
        data->win_data = window->driverdata;
        cursor->driverdata = (void *) data;

        /* Assume ARGB8888 */
        SDL_assert(surface->format->format == SDL_PIXELFORMAT_ARGB8888);
        SDL_assert(surface->pitch == surface->w * 4);

        /* Allocate shared memory buffer for this cursor */
        if (create_buffer_from_shm (data,
                                    surface->w,
                                    surface->h,
                                    WL_SHM_FORMAT_XRGB8888) < 0)
        {
            free (cursor->driverdata);
            free (cursor);
            return NULL;
        }

        SDL_memcpy(data->shm_data,
                   surface->pixels,
                   surface->h * surface->pitch);

        data->surface = wl_compositor_create_surface(ecore_wl_compositor_get());

        data->hot_x = hot_x;
        data->hot_y = hot_y;
        data->w = surface->w;
        data->h = surface->h;
    }

    return cursor;
}


static void
Tizen_FreeCursor(SDL_Cursor *cursor)
{
    Tizen_CursorData *d;

    if (!cursor)
        return;

    d = cursor->driverdata;

    /* Probably not a cursor we own */
    if (!d)
        return;

    if (d->buffer && !d->cursor)
        wl_buffer_destroy(d->buffer);

    if (d->surface)
        wl_surface_destroy(d->surface);

    /* Not sure what's meant to happen to shm_data */
    free (cursor->driverdata);
    SDL_free(cursor);
}

static int
Tizen_ShowCursor(SDL_Cursor *cursor)
{
    if (cursor)
    {
        Tizen_CursorData *data = cursor->driverdata;
        SDL_WindowData *win_data = data->win_data;
        ecore_wl_window_buffer_attach(win_data->window, data->buffer, 0,0);
        ecore_wl_input_pointer_set(ecore_wl_input_get(), data->surface, data->hot_x, data->hot_y);
    }
    else
    {
        ecore_wl_input_pointer_set(ecore_wl_input_get(), NULL, 0, 0);
    }
    
    return 0;
}

void
Tizen_InitMouse(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Tizen_CreateCursor;
    mouse->ShowCursor = Tizen_ShowCursor;
    mouse->FreeCursor = Tizen_FreeCursor;
}

void
Tizen_FiniMouse(void)
{
    /* This effectively assumes that nobody else touches SDL_Mouse which is effectively a singleton */
    SDL_Mouse *mouse = SDL_GetMouse();

    /* Free the current cursor if not the same pointer as
     * the default cursor */
    if (mouse->def_cursor != mouse->cur_cursor)
        Tizen_FreeCursor (mouse->cur_cursor);

    Tizen_FreeCursor (mouse->def_cursor);
    mouse->def_cursor = NULL;
    mouse->cur_cursor = NULL;

    mouse->CreateCursor =  NULL;
    mouse->CreateSystemCursor = NULL;
    mouse->ShowCursor = NULL;
    mouse->FreeCursor = NULL;
    mouse->WarpMouse = NULL;
    mouse->SetRelativeMouseMode = NULL;
}

Eina_Bool
__tizen_cb_event_mousedown_change(void *data, int type, void *event)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    if (!event) return ECORE_CALLBACK_PASS_ON;

    Ecore_Event_Mouse_Button *e = event;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "mouse down (%d x %d)",e->x,e->y);
    SDL_SendMouseMotion(_this->current_glwin, 0, 0,  e->x, e->y);
    SDL_SendMouseButton(_this->current_glwin, 0, SDL_PRESSED, SDL_BUTTON_LEFT);
    return ECORE_CALLBACK_PASS_ON;
}

Eina_Bool
__tizen_cb_event_mouseup_change(void *data, int type, void *event)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    if (!event) return ECORE_CALLBACK_PASS_ON;

    Ecore_Event_Mouse_Button *e = event;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "mouse up (%d x %d)",e->x,e->y);
    SDL_SendMouseMotion(_this->current_glwin, 0, 0,  e->x, e->y);
    SDL_SendMouseButton(_this->current_glwin, 0, SDL_RELEASED, SDL_BUTTON_LEFT);
    return ECORE_CALLBACK_PASS_ON;
}

Eina_Bool
__tizen_cb_event_mousemove_change(void *data, int type, void *event)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();

    if (!event) return ECORE_CALLBACK_PASS_ON;

    Ecore_Event_Mouse_Move *e = event;
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "mouse move (%d x %d)",e->x,e->y);
    SDL_SendMouseMotion(_this->current_glwin, 0, 0,  e->x, e->y);

    return ECORE_CALLBACK_PASS_ON;
}




