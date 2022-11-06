#ifndef LANDER_H
#define LANDER_H
#include "sdlstuff.h"
#include "geometry.h"

typedef struct Lander {
  float x;
  float y;
  float angle;
  float xvel;
  float yvel;
} Lander;

extern const int STARTVEL;
extern Lander lander;
void renderLander(void);
void updateLander(void);
void landerEvent(SDL_Event event);

#endif