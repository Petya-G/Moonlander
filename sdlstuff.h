#ifndef SDLSTUFF_H
#define SDLSTUFF_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

extern const int WIDTH;
extern const int HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool init(void);
void shutdown(void);
#endif