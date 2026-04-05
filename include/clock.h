#pragma once

#include "types.h"

typedef struct
{
    u64 now;
    u64 last;
    double delta_time;
} Clock;

void clock_init(Clock* clock);
void clock_tick(Clock* clock);
