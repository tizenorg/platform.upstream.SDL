/*
    SDL_tizen_main.c, placed in the public domain by samsung  5/23/16
*/
#include "SDL_config.h"

#ifdef __TIZEN__
#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_main.h"
#include <SDL_log.h>

#ifdef main
#undef main
#endif

int main(int argc, char *argv[])
{
    SDL_tizen_app_init(argc, argv);
    SDL_SetMainReady();
    (void)SDL_main(argc, argv);
    return 0;
}

#endif /* __TIZEN__ */

/* vi: set ts=4 sw=4 expandtab: */
