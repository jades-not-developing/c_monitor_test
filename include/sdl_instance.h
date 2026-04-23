#pragma once

#include <SDL2/SDL.h>

#include "types.h"

typedef enum
{
   SDL_INSTANCE_MAIN,
   SDL_INSTANCE_CONTROLLER,
} SDLInstanceType;

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

void sdl_set_color(const SDLInstance* i, SDLInstanceType type, u8 r, u8 g, u8 b);
void sdl_clear(const SDLInstance* i, SDLInstanceType type);
void sdl_get_window_size(const SDLInstance* i, SDLInstanceType type, i32* w, i32* h);
void sdl_present(const SDLInstance* i, SDLInstanceType type);
void sdl_fill_rect(const SDLInstance* i, SDLInstanceType type, const SDL_Rect* rect);