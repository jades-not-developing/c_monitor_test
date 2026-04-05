#include "clock.h"

#include <SDL2/SDL.h>

void clock_init(Clock* clock)
{
    clock->now = SDL_GetPerformanceCounter();
    clock->last = 0;
    clock->delta_time = 0;
}

void clock_tick(Clock* clock)
{
    clock->last = clock->now;
    clock->now = SDL_GetPerformanceCounter();

    clock->delta_time = ((f64)(clock->now - clock->last) * 1000 / (f64) SDL_GetPerformanceFrequency());
}
