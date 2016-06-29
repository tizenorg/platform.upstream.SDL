/*
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/

/* Simple test of the SDL threading code */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "SDL.h"

static SDL_TLSID tls;
static int alive = 0;

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{
    SDL_Quit();
    exit(rc);
}

int SDLCALL
ThreadFunc(void *data)
{
    SDL_TLSSet(tls, "baby thread", NULL);
    SDLTest_Log("Started thread %s: My thread id is %lu, thread data = %s\n",
           (char *) data, SDL_ThreadID(), (const char *)SDL_TLSGet(tls));
    while (alive) {
        SDLTest_Log("Thread '%s' is alive!\n", (char *) data);
        SDL_Delay(1 * 1000);
    }
    SDLTest_Log("Thread '%s' exiting!\n", (char *) data);
    return (0);
}

static void
killed(int sig)
{
    SDLTest_Log("Killed with SIGTERM, waiting 5 seconds to exit\n");
    SDL_Delay(5 * 1000);
    alive = 0;
    quit(0);
}

int
main(int argc, char *argv[])
{
	SDL_SetMainReady();
    SDL_Thread *thread;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Load the SDL library */
    if (SDL_Init(0) < 0) {
        SDLTest_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return (1);
    }

    tls = SDL_TLSCreate();
    SDL_assert(tls);
    SDL_TLSSet(tls, "main thread", NULL);
    SDLTest_Log("Main thread data initially: %s\n", (const char *)SDL_TLSGet(tls));

    alive = 1;
    thread = SDL_CreateThread(ThreadFunc, "One", "#1");
    if (thread == NULL) {
        SDLTest_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create thread: %s\n", SDL_GetError());
        quit(1);
    }
    SDL_Delay(5 * 1000);
    SDLTest_Log("Waiting for thread #1\n");
    alive = 0;
    SDL_WaitThread(thread, NULL);

    SDLTest_Log("Main thread data finally: %s\n", (const char *)SDL_TLSGet(tls));

    alive = 1;
    signal(SIGTERM, killed);
    thread = SDL_CreateThread(ThreadFunc, "Two", "#2");
    if (thread == NULL) {
        SDLTest_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create thread: %s\n", SDL_GetError());
        quit(1);
    }
    raise(SIGTERM);

    SDL_Quit();                 /* Never reached */
    return (0);                 /* Never reached */
}
