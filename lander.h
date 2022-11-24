#ifndef LANDER_H
#define LANDER_H
#include "sdlstuff.h"
#include "geometry.h"
#include "level.h"
#include "score.h"

typedef struct Lander {
  Point pos;
  Point vel;
  float angle;
  int fuel;
  Uint32 elapsed;
} Lander;

extern const float g;
extern Line landerLines[];
void updateLander(Lander *lander, Line landerLines[]);
void landerEvent(Lander *lander, SDL_Event event, double dt);
Lander landerReset();
#endif