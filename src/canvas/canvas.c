#include "canvas.h"

#include "macros.h"

// TODO: create a way to load these from a buffer or a file, maybe with a config file?
const Color COLOR_FRAMES[] = {
    /// Slightly Muted RGB
    {255,50,50},
    {50,255,50},
    {50,50,255},

    /// Pure RGB
    // {255,0,0},
    // {0,255,0},
    // {0,0,255},
};

bool color_eq(Color c1, Color c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

void test_canvas_init(TestCanvas* canvas)
{
    canvas->previous_color = canvas->current_color = COLOR_FRAMES[0];
}

void test_canvas_previous_color(TestCanvas* canvas)
{
    if (canvas->animating)
        canvas->previous_color = canvas->current_color;

    if (canvas->color_frame <= 0)
        canvas->color_frame = ARRAY_LEN(COLOR_FRAMES) - 1;
    else
        canvas->color_frame--;

    canvas->animation_direction = DIRECTION_BACKWARD;
    canvas->current_color = COLOR_FRAMES[canvas->color_frame];
    canvas->wipe_percentage = 0;
    canvas->animating = true;
}

void test_canvas_next_color(TestCanvas* canvas)
{
    if (canvas->animating)
        canvas->previous_color = canvas->current_color;

    if (canvas->color_frame >= ARRAY_LEN(COLOR_FRAMES) - 1)
        canvas->color_frame = 0;
    else
        canvas->color_frame++;

    canvas->animation_direction = DIRECTION_FORWARD;
    canvas->current_color = COLOR_FRAMES[canvas->color_frame];
    canvas->wipe_percentage = 0;
    canvas->animating = true;
}

