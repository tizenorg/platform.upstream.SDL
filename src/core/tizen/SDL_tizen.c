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
#include <appcore-efl.h>

typedef enum {
    APP_STATE_NOT_RUNNING,
    APP_STATE_CREATING,
    APP_STATE_RUNNING,
} app_state_e;

struct ui_app_context {
    char *package;
    char *app_name;
    app_state_e state;
    void *callback;
    void *data;
};

/* TODO  ::
 * Impplementation of serveral app core callback function for SDL Application and App Core
 * */

static int
_tizen_app_create(void *data)
{
    fprintf(stderr,"%s:%d\n",__FUNCTION__, __LINE__);
    return 0;
}

static int
_tizen_app_terminate(void *data)
{
    fprintf(stderr,"%s:%d\n",__FUNCTION__, __LINE__);
    return 0;
}

static int
_tizen_app_pause (void *data)
{
    fprintf(stderr,"%s:%d\n",__FUNCTION__, __LINE__);
    return 0;
}

static int
_tizen_app_resume(void *data)
{
    fprintf(stderr,"%s:%d\n",__FUNCTION__, __LINE__);
    return 0;
}

static int
_tizen_app_reset(bundle *bun, void *data)
{
    fprintf(stderr,"%s:%d\n",__FUNCTION__, __LINE__);
    return 0;
}

int
SDL_tizen_app_init(int argc, char *argv[])
{
    struct ui_app_context app_context = {
        .package = NULL,
        .app_name = NULL,
        .state = APP_STATE_NOT_RUNNING,
        .callback = NULL,
        .data = NULL,
    };

    struct appcore_ops appcore_context = {
        .data = &app_context,
        .create = _tizen_app_create,
        .terminate = _tizen_app_terminate,
        .pause = _tizen_app_pause,
        .resume = _tizen_app_resume,
        .reset = _tizen_app_reset,
    };

    if (argc < 1 || argv == NULL)
    {
        fprintf(stderr,"%s: APP_ERROR_INVALID_PARAMETER",__FUNCTION__);
        return 0;
    }

    if (app_context.state != APP_STATE_NOT_RUNNING)
    {
        fprintf(stderr,"%s: APP_STATE_NOT_RUNNING\n",__FUNCTION__);
        return 0;
    }

    /* TODO  ::
     * At first, check the necessary calling app_get_id()/app_get_package_app_name() while app_init.
     * If necessary, help these functions can be export.
     * After that, determine the implementation of them.
     * */
#if 0
    if (app_get_id(&(app_context.package)) != 0)
    {
        fprintf(stderr,"%s: APP_ERROR_INVALID_CONTEXT",__FUNCTION__);
        return 0;
    }

    if (app_get_package_app_name(app_context.package, &(app_context.app_name)) != 0)
    {
        free(app_context.package);
        fprintf(stderr,"%s: APP_ERROR_INVALID_CONTEXT",__FUNCTION__);
        return 0;
    }
#endif
    return appcore_efl_init(app_context.app_name, &argc, &argv, &appcore_context);
}

void
SDL_tizen_app_exit(void)
{
    appcore_efl_fini();
}
#endif
