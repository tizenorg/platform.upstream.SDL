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

#if SDL_VIDEO_DRIVER_TIZEN

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "SDL_stdinc.h"
#include "../../events/SDL_events_c.h"
#include "../../core/tizen/SDL_tizen.h"

#include "SDL_tizenvideo.h"
#include "SDL_tizenevents_c.h"
#include "SDL_tizenwindow.h"
#include "SDL_tizenopengles.h"
#include "SDL_tizenmouse.h"
#include "SDL_tizentouch.h"
#include "SDL_tizenkeyboard.h"


#define TIZENVID_DRIVER_NAME "tizen"

/* Initialization/Query functions */
static int
Tizen_VideoInit(_THIS);

static void
Tizen_GetDisplayModes(_THIS, SDL_VideoDisplay *sdl_display);
static int
Tizen_SetDisplayMode(_THIS, SDL_VideoDisplay *display, SDL_DisplayMode *mode);

static void
Tizen_VideoQuit(_THIS);

static void
__tizen_add_display(SDL_VideoData *d, uint32_t id)
{
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    static char *display_name = "tizen";

    SDL_zero(display);
    SDL_zero(mode);

    display.name = display_name;

    ecore_wl_screen_size_get(&mode.w, &mode.h);
    mode.refresh_rate = 60; //Hz
    SDL_AddDisplayMode(&display, &mode);

    display.current_mode = mode;
    display.desktop_mode = mode;

    SDL_AddVideoDisplay(&display);
}

/* Wayland driver bootstrap functions */
static int
Tizen_Available(void)
{
    return 1;
}

static void
Tizen_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

static SDL_VideoDevice *
Tizen_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;

    /* Initialize all variables that we clean on shutdown */
    device = SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return NULL;
    }

    /* Tizen video */
    device->VideoInit				= Tizen_VideoInit;
    device->VideoQuit 				= Tizen_VideoQuit;
    device->SetDisplayMode 			= Tizen_SetDisplayMode;
    device->GetDisplayModes 		= Tizen_GetDisplayModes;
    device->free					= Tizen_DeleteDevice;

    device->PumpEvents = Tizen_PumpEvents;

    device->GL_SwapWindow = Tizen_GLES_SwapWindow;
    device->GL_GetSwapInterval = Tizen_GLES_GetSwapInterval;
    device->GL_SetSwapInterval = Tizen_GLES_SetSwapInterval;
    device->GL_MakeCurrent = Tizen_GLES_MakeCurrent;
    device->GL_CreateContext = Tizen_GLES_CreateContext;
    device->GL_LoadLibrary = Tizen_GLES_LoadLibrary;
    device->GL_UnloadLibrary = Tizen_GLES_UnloadLibrary;
    device->GL_GetProcAddress = Tizen_GLES_GetProcAddress;
    device->GL_DeleteContext = Tizen_GLES_DeleteContext;

    device->CreateWindow = Tizen_CreateWindow;
    device->ShowWindow = Tizen_ShowWindow;
    device->SetWindowFullscreen = Tizen_SetWindowFullscreen;
    device->SetWindowSize = Tizen_SetWindowSize;
    device->DestroyWindow = Tizen_DestroyWindow;
    device->SetWindowHitTest = Tizen_SetWindowHitTest;
    device->GetWindowWMInfo = Tizen_GetWindowWMInfo;

    /* Text input */
    device->StartTextInput = Tizen_StartTextInput;
    device->StopTextInput = Tizen_StopTextInput;
    //device->SetTextInputRect = Tizen_SetTextInputRect;

    /* Screen keyboard */
    device->HasScreenKeyboardSupport = Tizen_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Tizen_ShowScreenKeyboard;
    //device->HideScreenKeyboard = Tizen_HideScreenKeyboard;
    device->IsScreenKeyboardShown = Tizen_IsScreenKeyboardShown;

    return device;
}

VideoBootStrap TIZEN_bootstrap = {
    TIZENVID_DRIVER_NAME, "SDL tizen video driver",
    Tizen_Available, Tizen_CreateDevice
};

int
Tizen_VideoInit(_THIS)
{
    SDL_VideoData *data = SDL_malloc(sizeof * data);

    if (data == NULL)
        return SDL_OutOfMemory();
    memset(data, 0, sizeof * data);

    _this->driverdata = data;

    ecore_wl_init(NULL);
    __tizen_add_display(data, 0);

    Tizen_InitWindow(_this);
    Tizen_InitMouse();
    return 0;
}

static void
Tizen_GetDisplayModes(_THIS, SDL_VideoDisplay *sdl_display)
{

}

static int
Tizen_SetDisplayMode(_THIS, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    return SDL_Unsupported();
}

void
Tizen_VideoQuit(_THIS)
{
    SDL_VideoData *data = _this->driverdata;

    Tizen_DeinitWindow(_this);
    Tizen_FiniKeyboard();
    SDL_tizen_app_exit();
    ecore_wl_shutdown();
    free(data);

    _this->driverdata = NULL;
    Tizen_FiniMouse();
}


#endif /* SDL_VIDEO_DRIVER_TIZEN */

/* vi: set ts=4 sw=4 expandtab: */
