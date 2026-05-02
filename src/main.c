#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "types.h"
#include "clock.h"
#include "canvas.h"
#include "sdl_instance.h"
#include "fs.h"
#include "timer.h"

int main()
{
    SDLInstance instance = {0};
    sdl_init(&instance);

    Clock clock = {0};
    clock_init(&clock);

    TestCanvas canvas = {0};
    test_canvas_init(&canvas);

    Timer test_timer = {0};

    i32 mx = 0;
    i32 my = 0;
    u8 running = 1;
    while (running)
    {
        clock_tick(&clock);
        timer_tick(&test_timer);
        // printf("%llu [%d]\n", test_timer.current / 1000, test_timer.in_progress);

        if (!test_timer.in_progress && test_timer.current != 0)
        {
            test_timer.current = 0;
            printf("done\n");
        }

        SDL_Event event;
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT)
            {
                running = 0;
                break;
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                if (mx != event.motion.x || my != event.motion.y)
                {
                    printf("mouse moved");
                }

                mx = event.motion.x;
                my = event.motion.y;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)     test_canvas_next_color(&canvas);
                else if (event.key.keysym.sym == SDLK_LEFT) test_canvas_previous_color(&canvas);

                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    test_timer.target = 3000;
                    timer_start(&test_timer);
                }
            }
        }

        sdl_set_color(&instance, SDL_INSTANCE_MAIN, 0, 0, 0);

        test_canvas_update(&instance, &clock, &canvas);
    }

    sdl_destroy(&instance);

    return 0;
}