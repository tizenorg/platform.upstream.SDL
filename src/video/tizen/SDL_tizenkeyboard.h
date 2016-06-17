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
#include "../SDL_sysvideo.h"
#include "SDL_tizenwindow.h"

#include <Ecore_Wayland.h>
#include <Ecore_IMF.h>

/*
#include "SDL_tizenvideo.h"
#include "SDL_tizenwindow.h"
#include "SDL_events.h"
*/
typedef struct _TizenKeyboard TizenKeyboard;
struct _TizenKeyboard
{
    Ecore_IMF_Context     *imf_context;
};

static TizenKeyboard keyboard;

extern void Tizen_FiniKeyboard(void);

extern void Tizen_StartTextInput(_THIS);
extern void Tizen_StopTextInput(_THIS);
extern void Tizen_SetTextInputRect(void);

extern SDL_bool Tizen_HasScreenKeyboardSupport(_THIS);
extern void Tizen_ShowScreenKeyboard(_THIS, SDL_Window * window);
extern void Tizen_HideScreenKeyboard(_THIS, SDL_Window * window);
extern SDL_bool  Tizen_IsScreenKeyboardShown(_THIS, SDL_Window * window);
