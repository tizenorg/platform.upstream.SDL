/*
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#include <stdio.h>
#include "SDL.h"

static void
print_devices(int iscapture)
{
    const char *typestr = ((iscapture) ? "capture" : "output");
    int n = SDL_GetNumAudioDevices(iscapture);

    SDLTest_Log("%s devices:\n", typestr);

    if (n == -1)
        SDLTest_Log("  Driver can't detect specific %s devices.\n\n", typestr);
    else if (n == 0)
        SDLTest_Log("  No %s devices found.\n\n", typestr);
    else {
        int i;
        for (i = 0; i < n; i++) {
            SDLTest_Log("  %s\n", SDL_GetAudioDeviceName(i, iscapture));
        }
        SDLTest_Log("\n");
    }
}

int
main(int argc, char **argv)
{
	SDL_tizen_app_init(argc, argv);
	SDL_SetMainReady();
    int n;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Load the SDL library */
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDLTest_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return (1);
    }

    /* Print available audio drivers */
    n = SDL_GetNumAudioDrivers();
    if (n == 0) {
        SDLTest_Log("No built-in audio drivers\n\n");
    } else {
        int i;
        SDLTest_Log("Built-in audio drivers:\n");
        for (i = 0; i < n; ++i) {
            SDLTest_Log("  %s\n", SDL_GetAudioDriver(i));
        }
        SDLTest_Log("\n");
    }

    SDLTest_Log("Using audio driver: %s\n\n", SDL_GetCurrentAudioDriver());

    print_devices(0);
    print_devices(1);

    SDL_Quit();
    return 0;
}
