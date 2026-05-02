#include <SDL_timer.h>

#include "timer.h"

void timer_init(Timer* timer)
{
    timer->data.last_ticks = SDL_GetTicks();
}

void timer_start(Timer* timer)
{
    timer->current = 0;
    timer->in_progress = true;
}

void timer_tick(Timer* timer)
{
    if (timer->in_progress && timer->current < timer->target)
    {
        u32 ticks_current = SDL_GetTicks();
        timer->current += ticks_current - timer->data.last_ticks;
        timer->data.last_ticks = ticks_current;
    }
    else
    {
        timer->in_progress = false;
    }
}
