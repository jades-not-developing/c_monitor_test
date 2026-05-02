#pragma once

#include "types.h"

#ifdef SDL_BACKEND
typedef struct
{
    u32 last_ticks;
} TimerInternalData;
#else
#error No backend specified, try building with the SDL_BACKEND flag set
#endif

/// This is going to be in milliseconds for now
// TODO: allow different units to be used for `target` (e.g. seconds)
typedef struct
{
    usize target;

    usize current;
    bool in_progress;

    TimerInternalData data;
} Timer;

void timer_init(Timer* timer);
void timer_tick(Timer* timer);

/// If the timer is not running currently, start counting up to the target, if it is
/// currently running, reset the timer
void timer_start(Timer* timer);