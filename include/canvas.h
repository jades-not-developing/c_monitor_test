#pragma once

#include "types.h"
#include "clock.h"

#include <SDL2/SDL.h>

#include "sdl_instance.h"

typedef struct
{
    u8 r;
    u8 g;
    u8 b;
} Color;

bool color_eq(Color c1, Color c2);

typedef enum
{
    DIRECTION_FORWARD = 0,
    DIRECTION_BACKWARD,
} AnimationDirection;

typedef struct
{
    f64 wipe_percentage;
    Color previous_color;
    Color current_color;

    u8 color_frame;
    bool animating;
    AnimationDirection animation_direction;
} TestCanvas;

void test_canvas_init(TestCanvas* canvas);
void test_canvas_previous_color(TestCanvas* canvas);
void test_canvas_next_color(TestCanvas* canvas);

#ifdef SDL_BACKEND
void test_canvas_update(SDLInstance* i, Clock* clock, TestCanvas* canvas);
#endif
