#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "types.h"
#include "clock.h"
#include "canvas.h"
#include "sdl_instance.h"

int main()
{
    SDLInstance instance = {0};
    sdl_init(&instance);


    Clock clock = {0};
    clock_init(&clock);

    TestCanvas canvas = {0};
    test_canvas_init(&canvas);

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
                if (event.key.keysym.sym == SDLK_RIGHT)     test_canvas_next_color(&canvas);
                else if (event.key.keysym.sym == SDLK_LEFT) test_canvas_previous_color(&canvas);
            }
        }

        sdl_set_color(&instance, SDL_INSTANCE_MAIN, 0, 0, 0);

        test_canvas_update(&instance, &clock, &canvas);
    }

    sdl_destroy(&instance);

    return 0;
}
