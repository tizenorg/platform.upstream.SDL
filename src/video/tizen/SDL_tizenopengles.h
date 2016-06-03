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

#ifndef _SDL_tizenopengles_h
#define _SDL_tizenopengles_h

#include "../SDL_sysvideo.h"
#include "../SDL_egl_c.h"

typedef struct SDL_PrivateGLESData {
} SDL_PrivateGLESData;

/* OpenGLES functions */
#define Tizen_GLES_GetAttribute SDL_EGL_GetAttribute
#define Tizen_GLES_GetProcAddress SDL_EGL_GetProcAddress
#define Tizen_GLES_UnloadLibrary SDL_EGL_UnloadLibrary
#define Tizen_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define Tizen_GLES_GetSwapInterval SDL_EGL_GetSwapInterval

extern int Tizen_GLES_LoadLibrary(_THIS, const char *path);
extern SDL_GLContext Tizen_GLES_CreateContext(_THIS, SDL_Window *window);
extern void Tizen_GLES_SwapWindow(_THIS, SDL_Window *window);
extern int Tizen_GLES_MakeCurrent(_THIS, SDL_Window *window, SDL_GLContext context);
extern void Tizen_GLES_DeleteContext(_THIS, SDL_GLContext context);

#endif /* _SDL_tizenopengles_h */
