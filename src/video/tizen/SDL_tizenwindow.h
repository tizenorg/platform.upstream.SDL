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

#ifndef _SDL_tizenwindow_h
#define _SDL_tizenwindow_h

#include "../SDL_sysvideo.h"
#include "SDL_syswm.h"

#include "SDL_tizenvideo.h"

typedef struct {
    uint32_t id;

    Ecore_Wl_Window *window;
    struct wl_egl_window *egl_window;
    EGLSurface egl_surface;
} SDL_WindowData;

extern void Tizen_ShowWindow(_THIS, SDL_Window *window);
extern void Tizen_SetWindowFullscreen(_THIS, SDL_Window *window,
                                      SDL_VideoDisplay *_display,
                                      SDL_bool fullscreen);
extern int Tizen_CreateWindow(_THIS, SDL_Window *window);
extern void Tizen_SetWindowSize(_THIS, SDL_Window *window);
extern void Tizen_DestroyWindow(_THIS, SDL_Window *window);

extern SDL_bool Tizen_GetWindowWMInfo(_THIS, SDL_Window *window, SDL_SysWMinfo *info);
extern int Tizen_SetWindowHitTest(SDL_Window *window, SDL_bool enabled);

extern int Tizen_InitWindow(_THIS);
extern void Tizen_DeinitWindow(_THIS);

#endif /* _SDL_tizenwindow_h */

/* vi: set ts=4 sw=4 expandtab: */
