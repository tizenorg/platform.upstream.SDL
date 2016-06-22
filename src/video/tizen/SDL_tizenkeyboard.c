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

#include "SDL_tizenkeyboard.h"
#include "SDL_log.h"

/*
    Tizen Keyboard
*/

void
_ecore_imf_event_commit_cb(void *data, Ecore_IMF_Context *ctx EINA_UNUSED, void *event_info)
{
    char *commit_str = (char *)event_info;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "commit string : %s\n", commit_str);
    SDL_SendKeyboardText(commit_str);
    return;
}

void
_ecore_imf_event_state_change_cb(void *data, Ecore_IMF_Context *ctx EINA_UNUSED, int value)
{
    //ECORE_IMF_INPUT_PANEL_STATE_SHOW : 0
    //ECORE_IMF_INPUT_PANEL_STATE_HIDE : 1
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Keyboard State  : %d\n", value);
    return;
}

void Tizen_InitKeyboard(_THIS)
{
    ecore_imf_init();

    memset(&keyboard, 0, sizeof(keyboard));

    const char *default_id = ecore_imf_context_default_id_get();
    if (!default_id)
      {
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't create ecore_imf_context\n");
         return;
      }

    keyboard.imf_context = ecore_imf_context_add(default_id);

    SDL_Window *window = _this->windows;
    SDL_WindowData *wind = window->driverdata;

    ecore_imf_context_client_window_set(keyboard.imf_context, (void*)wind->id);

    ecore_imf_context_event_callback_add(keyboard.imf_context, ECORE_IMF_CALLBACK_COMMIT , _ecore_imf_event_commit_cb, NULL);
    ecore_imf_context_input_panel_event_callback_add (keyboard.imf_context, ECORE_IMF_INPUT_PANEL_STATE_EVENT, _ecore_imf_event_state_change_cb, NULL);

    ecore_imf_context_cursor_position_set(keyboard.imf_context, 0);
    ecore_imf_context_focus_out(keyboard.imf_context);
    ecore_imf_context_input_panel_hide(keyboard.imf_context);

}

void Tizen_FiniKeyboard(void)
{
    if(keyboard.imf_context == NULL)
        return;

    ecore_imf_context_del(keyboard.imf_context);
    keyboard.imf_context = NULL;

    ecore_imf_shutdown();
}

void
Tizen_StartTextInput(_THIS)
{
    if (!_this) {
        return SDL_SetError("Video subsystem must be initialized");
    }

    if(keyboard.imf_context == NULL)
      Tizen_InitKeyboard(_this);

    Tizen_ShowScreenKeyboard(_this, NULL);
}


void
Tizen_StopTextInput(_THIS)
{
   if (!_this) return;
   if (keyboard.imf_context)
     {
        Tizen_HideScreenKeyboard(_this, _this->windows);
     }
}

void Tizen_SetTextInputRect(void)
{
}


SDL_bool
Tizen_HasScreenKeyboardSupport(_THIS)
{
    return SDL_TRUE;
}


void
Tizen_ShowScreenKeyboard(_THIS, SDL_Window * window)
{
    if (!keyboard.imf_context)
          return;

    ecore_imf_context_focus_in(keyboard.imf_context);
    ecore_imf_context_input_panel_show(keyboard.imf_context);
}

void
Tizen_HideScreenKeyboard(_THIS, SDL_Window * window)
{
    if (!keyboard.imf_context)
          return;

    ecore_imf_context_focus_out(keyboard.imf_context);
    ecore_imf_context_input_panel_hide(keyboard.imf_context);
}

SDL_bool
Tizen_IsScreenKeyboardShown(_THIS, SDL_Window * window)
{
    if (!keyboard.imf_context)
          return;
    //EAPI Ecore_IMF_Input_Panel_State  ecore_imf_context_input_panel_state_get (Ecore_IMF_Context *ctx)
    return ecore_imf_context_input_panel_state_get(keyboard.imf_context);
}
