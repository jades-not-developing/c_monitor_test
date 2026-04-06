#pragma once

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window* main_window;
    SDL_Renderer* main_renderer;

    //TODO: controller_window and controller_renderer

    bool is_running;

    SDL_Event event;
} SDLInstance;

void sdl_init(SDLInstance* i);
void sdl_destroy(SDLInstance* i);