#include <stdio.h>
#include "SDL.h"

/* !!! FIXME: rewrite this to be wired in to test framework. */

#define RESIZE_BORDER 20

const SDL_Rect drag_areas[] = {
    { 20, 20, 100, 100 },
    { 200, 70, 100, 100 },
    { 400, 90, 100, 100 }
};

static const SDL_Rect *areas = drag_areas;
static int numareas = SDL_arraysize(drag_areas);

static SDL_HitTestResult
hitTest(SDL_Window *window, const SDL_Point *pt, void *data)
{
    int i;
    int w, h;

    for (i = 0; i < numareas; i++) {
        if (SDL_PointInRect(pt, &areas[i])) {
            SDLTest_Log("HIT-TEST: DRAGGABLE\n");
            return SDL_HITTEST_DRAGGABLE;
        }
    }

    SDL_GetWindowSize(window, &w, &h);

    #define REPORT_RESIZE_HIT(name) { \
        SDLTest_Log("HIT-TEST: RESIZE_" #name "\n"); \
        return SDL_HITTEST_RESIZE_##name; \
    }

    if (pt->x < RESIZE_BORDER && pt->y < RESIZE_BORDER) {
        REPORT_RESIZE_HIT(TOPLEFT);
    } else if (pt->x > RESIZE_BORDER && pt->x < w - RESIZE_BORDER && pt->y < RESIZE_BORDER) {
        REPORT_RESIZE_HIT(TOP);
    } else if (pt->x > w - RESIZE_BORDER && pt->y < RESIZE_BORDER) {
        REPORT_RESIZE_HIT(TOPRIGHT);
    } else if (pt->x > w - RESIZE_BORDER && pt->y > RESIZE_BORDER && pt->y < h - RESIZE_BORDER) {
        REPORT_RESIZE_HIT(RIGHT);
    } else if (pt->x > w - RESIZE_BORDER && pt->y > h - RESIZE_BORDER) {
        REPORT_RESIZE_HIT(BOTTOMRIGHT);
    } else if (pt->x < w - RESIZE_BORDER && pt->x > RESIZE_BORDER && pt->y > h - RESIZE_BORDER) {
        REPORT_RESIZE_HIT(BOTTOM);
    } else if (pt->x < RESIZE_BORDER && pt->y > h - RESIZE_BORDER) {
        REPORT_RESIZE_HIT(BOTTOMLEFT);
    } else if (pt->x < RESIZE_BORDER && pt->y < h - RESIZE_BORDER && pt->y > RESIZE_BORDER) {
        REPORT_RESIZE_HIT(LEFT);
    }

    SDLTest_Log("HIT-TEST: NORMAL\n");
    return SDL_HITTEST_NORMAL;
}
#ifdef main
#undef main
#endif

int main(int argc, char **argv)
{
	SDL_tizen_app_init(argc, argv);
	SDL_SetMainReady();
    int done = 0;
    SDL_Window *window;
    SDL_Renderer *renderer;

    /* !!! FIXME: check for errors. */
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Drag the red boxes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 1280, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (SDL_SetWindowHitTest(window, hitTest, NULL) == -1) {
        SDLTest_Log("Enabling hit-testing failed!\n");
        SDL_Quit();
        return 1;
    }

    while (!done)
    {
        SDL_Event e;
        int nothing_to_do = 1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 127, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRects(renderer, areas, SDL_arraysize(drag_areas));
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e)) {
            nothing_to_do = 0;

            switch (e.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    SDLTest_Log("button down!\n");
                    break;

                case SDL_MOUSEBUTTONUP:
                    SDLTest_Log("button up!\n");
                    break;

                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_MOVED) {
                        SDLTest_Log("Window event moved to (%d, %d)!\n", (int) e.window.data1, (int) e.window.data2);
                    }
                    break;

                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_f) {
                        done = 1;
                    } else if (e.key.keysym.sym == SDLK_x) {
                        if (!areas) {
                            areas = drag_areas;
                            numareas = SDL_arraysize(drag_areas);
                        } else {
                            areas = NULL;
                            numareas = 0;
                        }
                    }
                    break;

                case SDL_QUIT:
                    done = 1;
                    break;
            }
        }

        if (nothing_to_do) {
            SDL_Delay(50);
        }
    }

    SDL_Quit();
    return 0;
}
