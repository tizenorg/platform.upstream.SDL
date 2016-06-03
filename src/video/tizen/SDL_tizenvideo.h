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

#ifndef _SDL_tizenvideo_h
#define _SDL_tizenvideo_h

#include <EGL/egl.h>
#include <Ecore_Wayland.h>
#include <appcore-efl.h>

typedef struct {
    EGLDisplay edpy;
    EGLContext context;
    EGLConfig econf;

    Eina_Hash *windows;
} SDL_VideoData;

#ifdef ENABLE_DEBUG
#define TRACE_ENTER() printf("[SDL] %s:%d\n", __FUNCTION__, __LINE__)
#else
#define TRACE_ENTER()
#endif

#endif /* _SDL_tizenvideo_h */

/* vi: set ts=4 sw=4 expandtab: */
