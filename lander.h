#ifndef LANDER_H
#define LANDER_H
#include "sdlstuff.h"
#include "geometry.h"
#include "level.h"
#include <SDL2/SDL_rect.h>

typedef struct Lander {
  float x;
  float y;
  float angle;
  float xvel;
  float yvel;
  SDL_Rect rect;
} Lander;

extern const int STARTVEL;
extern SDL_Rect rect;
extern Lander lander;
void updateLander(void);
void landerEvent(SDL_Event event);

#endif