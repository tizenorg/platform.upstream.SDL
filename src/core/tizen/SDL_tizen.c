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
#include <stdio.h>
#include "../../SDL_internal.h"

#if __TIZEN__
#include "SDL_tizen.h"
#include "SDL_log.h"
#include "SDL_events.h"
#include <app_internal.h>
#include <app_extension.h>
#include <system_settings.h>

static int tizen_appcore_initialized = 0;
static appcore_context_h appcore_handle = NULL;
static ui_app_lifecycle_callback_s event_callback = {0,};
static app_event_handler_h handlers[5] = {NULL, };

/* TODO  ::
 * Impplementation of serveral app core callback function for SDL Application and App Core
 * */

static bool
_tizen_sdl_create(void *data)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_AppCore CreateCB");
    return true;
}

static void
_tizen_sdl_terminate(void *data)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_AppCore TermincateCB");
    SDL_SendQuit();
    SDL_SendAppEvent(SDL_APP_TERMINATING);
    return;
}

static void
_tizen_sdl_pause (void *data)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_AppCore PauseCB");
    SDL_SendAppEvent(SDL_APP_WILLENTERBACKGROUND);
    SDL_SendAppEvent(SDL_APP_DIDENTERBACKGROUND);
    return;
}

static void
_tizen_sdl_resume(void *data)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_AppCore ResumeCB");
    SDL_SendAppEvent(SDL_APP_WILLENTERFOREGROUND);
    SDL_SendAppEvent(SDL_APP_DIDENTERFOREGROUND);
    return;
}

static void
_tizen_sdl_control(app_control_h app_control, void *data)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL_AppCore ControlCB");
    return;
}

static void
_tizen_app_lang_changed(app_event_info_h event_info, void *user_data)
{
    /*APP_EVENT_LANGUAGE_CHANGED*/
    char *locale = NULL;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Language changedCB");
    system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
    free(locale);
    return;
}

static void
_tizen_app_orient_changed(app_event_info_h event_info, void *user_data)
{
    /*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "orient changedCB");
    app_device_orientation_e orientation;
    app_event_get_device_orientation(event_info, &orientation);

    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = SDL_ROTATEEVENT;
    event.user.code = NULL;
    event.window.data1 = (void*)orientation;
    event.user.data2 = -1;

    SDL_PushEvent(&event);
    return;
}

static void
_tizen_app_region_changed(app_event_info_h event_info, void *user_data)
{
    /*APP_EVENT_REGION_FORMAT_CHANGED*/
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "region changedCB");
}

static void
_tizen_app_low_battery(app_event_info_h event_info, void *user_data)
{
    /*APP_EVENT_LOW_BATTERY*/
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "low battery CB");
}

static void
_tizen_app_low_memory(app_event_info_h event_info, void *user_data)
{
    /*APP_EVENT_LOW_MEMORY*/
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "low memory CB");
    SDL_SendAppEvent(SDL_APP_LOWMEMORY);
}

int
SDL_tizen_app_init(int argc, char *argv[])
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL Tizen App initialize");
    if (tizen_appcore_initialized)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Already initialized!");
        return 0;
    }
    tizen_appcore_initialized = 1;
    if (argc < 1 || argv == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "APP_ERROR_INVALID_PARAMETER");
        return 0;
    }

    event_callback.create = _tizen_sdl_create;
    event_callback.terminate = _tizen_sdl_terminate;
    event_callback.pause = _tizen_sdl_pause;
    event_callback.resume = _tizen_sdl_resume;
    event_callback.app_control = _tizen_sdl_control;

    ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, _tizen_app_low_battery, NULL);
    ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, _tizen_app_low_memory, NULL);
    ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, _tizen_app_orient_changed, NULL);
    ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, _tizen_app_lang_changed, NULL);
    ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, _tizen_app_region_changed, NULL);

    return ui_app_init(argc, argv, &event_callback, NULL, &appcore_handle);
}

void
SDL_tizen_app_exit(void)
{
    ui_app_fini(appcore_handle);
}
#endif
