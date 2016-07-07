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

#if SDL_VIDEO_DRIVER_TIZEN && SDL_VIDEO_OPENGL_EGL

#include "../SDL_sysvideo.h"
#include "../../events/SDL_windowevents_c.h"
#include "../SDL_egl_c.h"
#include "SDL_tizenwindow.h"
#include "SDL_tizenvideo.h"
#include "SDL_tizentouch.h"
#include "SDL_tizenkeyboard.h"

#include "SDL_tizenmouse.h"
#include "SDL_tizenevents_c.h"
#include "SDL_log.h"

#include <wayland-egl.h>

SDL_bool
Tizen_GetWindowWMInfo(_THIS, SDL_Window *window, SDL_SysWMinfo *info)
{
    return SDL_TRUE;
}

int
Tizen_SetWindowHitTest(SDL_Window *window, SDL_bool enabled)
{
    return 0;  /* just succeed, the real work is done elsewhere. */
}

void
Tizen_ShowWindow(_THIS, SDL_Window *window)
{
    SDL_WindowData *wind = window->driverdata;

    ecore_wl_window_show(wind->window);
}

void
Tizen_SetWindowFullscreen(_THIS, SDL_Window *window,
                          SDL_VideoDisplay *_display, SDL_bool fullscreen)
{
    /*DO NOTHING*/
}

int
Tizen_CreateWindow(_THIS, SDL_Window *window)
{
    SDL_VideoData *data = _this->driverdata;
    SDL_WindowData *wind;

    wind = calloc(1, sizeof * wind);
    if (wind == NULL)
        return SDL_OutOfMemory();

    window->driverdata = wind;

    if (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_GL_LoadLibrary(NULL);
        window->flags |= SDL_WINDOW_OPENGL;
    }

    if (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }
    if (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    wind->window = ecore_wl_window_new(NULL,
                                       window->x, window->y, window->w, window->h,
                                       ECORE_WL_WINDOW_BUFFER_TYPE_SHM);
    ecore_wl_window_surface_create(wind->window);

    wind->egl_window = wl_egl_window_create(ecore_wl_window_surface_get(wind->window), window->w, window->h);

    /* Create the GLES window surface */
    wind->egl_surface = SDL_EGL_CreateSurface(_this, (NativeWindowType) wind->egl_window);
    if (wind->egl_surface == EGL_NO_SURFACE) {
        return SDL_SetError("failed to create a window surface");
    }

    wind->id = ecore_wl_window_id_get(wind->window);
    eina_hash_add(data->windows, &wind->id, window);

    if(keyboard.imf_context == NULL)
        Tizen_InitKeyboard(_this);

    SDL_SetMouseFocus(window);

    return 0;
}

void
Tizen_SetWindowSize(_THIS, SDL_Window *window)
{
    SDL_WindowData *wind = window->driverdata;

    wl_egl_window_resize(wind->egl_window, window->w, window->h, 0, 0);
}

void
Tizen_DestroyWindow(_THIS, SDL_Window *window)
{
    SDL_VideoData *data = _this->driverdata;
    SDL_WindowData *wind = window->driverdata;

    if (data) {
        eina_hash_del(data->windows, &wind->id, window);

        SDL_EGL_DestroySurface(_this, wind->egl_surface);
        wl_egl_window_destroy(wind->egl_window);
        ecore_wl_window_free(wind->window);

        SDL_free(wind);
    }

    window->driverdata = NULL;
}

static SDL_Window*
__tizen_find_window(_THIS, Ecore_Wl_Window *ewin)
{
    SDL_VideoData *data = _this->driverdata;
    int id;

    id = ecore_wl_window_id_get(ewin);
    return (SDL_Window*)eina_hash_find(data->windows, &id);
}

static Eina_Bool
__tizen_cb_window_visibility_change(void *data, int type, void *event)
{
    _THIS = data;
    Ecore_Wl_Event_Window_Visibility_Change *ev;
    Ecore_Wl_Window *ew;
    SDL_Window *window;

    ev = event;
    ew = ecore_wl_window_find(ev->win);
    window = __tizen_find_window(_this, ew);

    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "visibility window: %p, ecore_wl_window: %p\n", window, ew);

    SDL_SendWindowEvent(window, SDL_WINDOWEVENT_SHOWN, 0, 0);
    SDL_SendWindowEvent(window, SDL_WINDOWEVENT_RESTORED, 0, 0);

    return ECORE_CALLBACK_PASS_ON;
}

int 
Tizen_InitWindow(_THIS)
{
    SDL_VideoData *data = _this->driverdata;

    data->windows = eina_hash_int32_new(NULL);
    
    ecore_event_handler_add(ECORE_WL_EVENT_WINDOW_VISIBILITY_CHANGE,
                        __tizen_cb_window_visibility_change, _this);
    ecore_event_handler_add(ECORE_EVENT_KEY_UP,
                        __tizen_cb_event_keyup_change,  NULL);
    ecore_event_handler_add(ECORE_EVENT_KEY_DOWN,
                        __tizen_cb_event_keydown_change,	NULL);

    ecore_event_handler_add(ECORE_EVENT_MOUSE_BUTTON_DOWN,
                        __tizen_cb_event_mousedown_change,	_this);
    ecore_event_handler_add(ECORE_EVENT_MOUSE_BUTTON_UP,
                        __tizen_cb_event_mouseup_change,	_this);
    ecore_event_handler_add(ECORE_EVENT_MOUSE_MOVE,
                        __tizen_cb_event_mousemove_change,	_this);

    return 0;
}

void
Tizen_DeinitWindow(_THIS)
{
    SDL_VideoData *data = _this->driverdata;

    eina_hash_free(data->windows);
}
#endif /* SDL_VIDEO_DRIVER_TIZEN && SDL_VIDEO_OPENGL_EGL */

/* vi: set ts=4 sw=4 expandtab: */
