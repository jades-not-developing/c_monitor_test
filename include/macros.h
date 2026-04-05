#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>

#define PANIC(...) { const char* err = SDL_GetError(); \
                   fprintf(stderr, __VA_ARGS__); \
                   fprintf(stderr, ": %s\n", err); \
                   exit(1); \
                   SDL_free((void*)err);}
