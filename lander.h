#ifndef LANDER_H
#define LANDER_H
#include "sdlstuff.h"
#include "geometry.h"
#include "level.h"
#include "score.h"

typedef struct Lander {
  Point pos;
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