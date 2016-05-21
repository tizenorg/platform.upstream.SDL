/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>
  Copyright 2015 Samsung Electronics co., Ltd. All Rights Reserved.

  Contact: Sangjin Lee <lsj119@samsung.com>

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
    SDL_WindowData *data;

    data = calloc(1, sizeof * data);
    if (data == NULL)
        return SDL_OutOfMemory();

    window->driverdata = data;

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

    data->window = ecore_wl_window_new(NULL,
                                       window->x, window->y, window->w, window->h,
                                       ECORE_WL_WINDOW_BUFFER_TYPE_SHM);
    ecore_wl_window_surface_create(data->window);

    data->egl_window = wl_egl_window_create(ecore_wl_window_surface_get(data->window), window->w, window->h);

    /* Create the GLES window surface */
    data->egl_surface = SDL_EGL_CreateSurface(_this, (NativeWindowType) data->egl_window);
    if (data->egl_surface == EGL_NO_SURFACE) {
        return SDL_SetError("failed to create a window surface");
    }

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
        SDL_EGL_DestroySurface(_this, wind->egl_surface);
        wl_egl_window_destroy(wind->egl_window);

        ecore_wl_window_free(wind->window);

        SDL_free(wind);
    }

    window->driverdata = NULL;
}

#endif /* SDL_VIDEO_DRIVER_TIZEN && SDL_VIDEO_OPENGL_EGL */

/* vi: set ts=4 sw=4 expandtab: */
