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
#include "SDL_tizenmouse.h"
#include "SDL_log.h"


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




