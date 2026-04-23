#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>

#define PANIC(...) { const char* err = SDL_GetError(); \
                   fprintf(stderr, __VA_ARGS__); \
                   fprintf(stderr, ": %s\n", err); \
                   exit(1); \
                   SDL_free((void*)err);}

#define TODO(...) { fprintf(stderr, "TODO: "); \
                  fprintf(stderr, __VA_ARGS__); \
                  fprintf(stderr, "\n"); \
                  exit(1); }

#define ARRAY_LEN(array) (sizeof(array)/sizeof(*(array)))
