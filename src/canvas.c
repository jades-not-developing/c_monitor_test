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

void test_canvas_update(SDLInstance* i, Clock* clock, TestCanvas* canvas)
{
    i32 w;
    i32 h;
    if (canvas->wipe_percentage == 0)
    {
        Color c = canvas->current_color;
        sdl_set_color(i, SDL_INSTANCE_MAIN, c.r, c.g, c.b);
        sdl_clear(i, SDL_INSTANCE_MAIN);
    }
    else if (canvas->wipe_percentage == 100)
    {
        Color c = canvas->current_color;
        sdl_set_color(i, SDL_INSTANCE_MAIN, c.r, c.g, c.b);
        sdl_clear(i, SDL_INSTANCE_MAIN);

        canvas->previous_color = canvas->current_color;
        canvas->wipe_percentage = 0;
        canvas->animating = false;
    } else
    {
        Color prev_c = canvas->previous_color;
        sdl_set_color(i, SDL_INSTANCE_MAIN, prev_c.r, prev_c.g, prev_c.b);
        sdl_clear(i, SDL_INSTANCE_MAIN);

        Color current_c = canvas->current_color;
        sdl_get_window_size(i, SDL_INSTANCE_MAIN, &w, &h);

        f64 normalized_percentage = canvas->wipe_percentage / 100.f;
        f64 easeOutQuart = 1.f - pow(1.f - normalized_percentage, 4.f);
        i32 width = (i32)((f32)(w + 1) * easeOutQuart);

        if (canvas->animation_direction == DIRECTION_FORWARD)
        {
            SDL_Rect r = {
                .x = 0,
                .y = 0,
                .w = width,
                .h = h,
             };
            sdl_set_color(i, SDL_INSTANCE_MAIN, current_c.r, current_c.g, current_c.b);
            sdl_fill_rect(i, SDL_INSTANCE_MAIN, &r);
        } else
        {
            SDL_Rect r = {
                .x = w - width,
                .y = 0,
                .w = width,
                .h = h,
             };
            sdl_set_color(i, SDL_INSTANCE_MAIN, current_c.r, current_c.g, current_c.b);
            sdl_fill_rect(i, SDL_INSTANCE_MAIN, &r);
        }
    }

    if (canvas->wipe_percentage < 100.f && !color_eq(canvas->current_color, canvas->previous_color))
    {
        canvas->wipe_percentage += 0.09f * clock->delta_time;
    }

    sdl_present(i, SDL_INSTANCE_MAIN);
}
