#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <stdio.h>

#include "macros.h"
#include "types.h"
#include "clock.h"

typedef struct
{
    u8 r;
    u8 g;
    u8 b;
} Color;

bool color_eq(Color c1, Color c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

typedef struct
{
    f64 wipe_percentage;
    Color previous_color;
    Color current_color;
} TestCanvas;

void test_canvas_update(SDL_Renderer* renderer, SDL_Window* window, Clock* clock, TestCanvas* canvas)
{
    i32 w;
    i32 h;
    if (canvas->wipe_percentage == 0)
    {
        Color c = canvas->current_color;
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 0xFF);
        SDL_RenderClear(renderer);
    }
    else if (canvas->wipe_percentage == 100)
    {
        Color c = canvas->current_color;
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 0xFF);
        SDL_RenderClear(renderer);

        canvas->previous_color = canvas->current_color;
        canvas->wipe_percentage = 0;
    } else
    {
        Color prev_c = canvas->previous_color;
        SDL_SetRenderDrawColor(renderer, prev_c.r, prev_c.g, prev_c.b, 0xFF);
        SDL_RenderClear(renderer);

        Color current_c = canvas->current_color;
        SDL_GetWindowSize(window, &w, &h);

        f64 normalized_percentage = canvas->wipe_percentage / 100.f;
        f64 easeOutQuart = 1.f - pow(1.f - normalized_percentage, 4.f);
        i32 width = (i32)((f32)(w + 1) * easeOutQuart);

        SDL_Rect r = {
            .x = 0,
            .y = 0,
            .w = width,
            .h = h,
         };
        SDL_SetRenderDrawColor(renderer, current_c.r, current_c.g, current_c.b, 0xFF);
        SDL_RenderFillRect(renderer, &r);
    }

    if (canvas->wipe_percentage < 100.f && !color_eq(canvas->current_color, canvas->previous_color))
    {
        canvas->wipe_percentage += 0.05f * clock->delta_time;
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        PANIC("SDL Failed to initialize");

    SDL_Window* main_window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN);
    SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

    Clock clock = {0};
    clock_init(&clock);

    TestCanvas canvas = {0};
    canvas.current_color = (Color){0};
    canvas.previous_color = (Color){0};


    u8 running = 1;
    while (running)
    {
        clock_tick(&clock);

        SDL_Event event;
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT)
            {
                running = 0;
                break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    canvas.current_color.r = 255;
                    canvas.wipe_percentage = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);

        test_canvas_update(main_renderer, main_window, &clock, &canvas);

        SDL_RenderPresent(main_renderer);
    }

    SDL_DestroyWindow(main_window);
    SDL_DestroyRenderer(main_renderer);



    SDL_Quit();

    return 0;
}