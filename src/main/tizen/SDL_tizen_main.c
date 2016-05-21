/*
    SDL_tizen_main.c, placed in the public domain by samsung  5/23/16
*/
#include "SDL_config.h"

#ifdef __TIZEN__

#include "SDL_main.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    setenv("SDL_TIZEN_MAIN_ARGC", (char*)argc, 1);
    setenv("SDL_TIZEN_MAIN_ARGV", (char*)argv, 1);

    SDL_SetMainReady();

    (void)SDL_main(argc, argv);
    return 0;
}

#endif /* __TIZEN__ */

/* vi: set ts=4 sw=4 expandtab: */
