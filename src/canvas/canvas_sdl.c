#include "canvas.h"

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
