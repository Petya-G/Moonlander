#ifndef LANDER_H
#define LANDER_H
#include "sdlstuff.h"
#include "geometry.h"
#include "level.h"

typedef struct Lander {
  float x;
  float y;
  float angle;
  float xvel;
  float yvel;
  int fuel;
} Lander;

extern Lander lander;
extern Uint32 elapsed;
void landerUpdate(void);
void landerEvent(SDL_Event event, double dt);
void landerReset();
#endif