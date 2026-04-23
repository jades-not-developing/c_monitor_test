#include "sdl_instance.h"

#include "macros.h"

void sdl_init(SDLInstance* i)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        PANIC("SDL Failed to initialize");

    i->main_window = SDL_CreateWindow("Monitor Color Test",
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

void sdl_set_color(const SDLInstance* i, SDLInstanceType type, u8 r, u8 g, u8 b)
{
    if (type == SDL_INSTANCE_MAIN)
    {
        SDL_SetRenderDrawColor(i->main_renderer, r, g, b, 255);
    }
    else
    {
        TODO("sdl_set_color: controller instance");
    }
}

void sdl_clear(const SDLInstance* i, SDLInstanceType type)
{
    if (type == SDL_INSTANCE_MAIN)
    {
       SDL_RenderClear(i->main_renderer);
    }
    else
    {
        TODO("sdl_clear: controller instance");
    }
}

void sdl_get_window_size(const SDLInstance* i, SDLInstanceType type, i32* w, i32* h)
{
    if (type == SDL_INSTANCE_MAIN)
    {
        SDL_GetWindowSize(i->main_window, w, h);
    }
    else
    {
        TODO("sdl_get_window_size: controller instance");
    }
}

void sdl_fill_rect(const SDLInstance* i, SDLInstanceType type, const SDL_Rect* rect)
{
    if (type == SDL_INSTANCE_MAIN)
    {
        SDL_RenderFillRect(i->main_renderer, rect);
    }
    else
    {
        TODO("sdl_render_present: controller instance");
    }
}

void sdl_present(const SDLInstance* i, SDLInstanceType type)
{
    if (type == SDL_INSTANCE_MAIN)
    {
        SDL_RenderPresent(i->main_renderer);
    }
    else
    {
        TODO("sdl_render_present: controller instance");
    }
}
