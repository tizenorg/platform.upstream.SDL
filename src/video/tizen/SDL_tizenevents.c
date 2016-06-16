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

#include "SDL_stdinc.h"
#include "SDL_assert.h"

#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"
#include "../../events/scancodes_xfree86.h"

#include "SDL_tizenvideo.h"
#include "SDL_tizenevents_c.h"
#include "SDL_tizenwindow.h"
#include "SDL_log.h"

void
Tizen_PumpEvents(_THIS)
{
    ecore_main_loop_iterate();
}

Eina_Bool
__tizen_cb_event_keyup_change(void *data, int type, void *event)
{
    if (!event) return ECORE_CALLBACK_PASS_ON;

    Ecore_Event_Key * e = event;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "key up: %d",e->keycode);
    SDL_SendKeyboardKey(SDL_RELEASED, e->keycode);

    return ECORE_CALLBACK_PASS_ON;
}

Eina_Bool
__tizen_cb_event_keydown_change(void *data, int type, void *event)
{
    if (!event) return ECORE_CALLBACK_PASS_ON;

    Ecore_Event_Key * e = event;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "key down: %d",e->keycode);
    SDL_SendKeyboardKey(SDL_PRESSED, e->keycode);

    return ECORE_CALLBACK_PASS_ON;
}


#endif /* SDL_VIDEO_DRIVER_TIZEN */

/* vi: set ts=4 sw=4 expandtab: */
