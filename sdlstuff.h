#ifndef SDLSTUFF_H
#define SDLSTUFF_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
//#include <SDL2/SDL_ttf.h>

extern const int WIDTH;
extern const int HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool init(void);
void update(void);
void shutdown(void);
#endif