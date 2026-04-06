#include "sdl_instance.h"

#include "macros.h"

void sdl_init(SDLInstance* i)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        PANIC("SDL Failed to initialize");

    i->main_window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    i->main_renderer = SDL_CreateRenderer(i->main_window, -1, SDL_RENDERER_ACCELERATED);
}

void sdl_destroy(SDLInstance* i)
{
    SDL_DestroyWindow(i->main_window);
    SDL_DestroyRenderer(i->main_renderer);
    SDL_Quit();

    i->is_running = false;
}