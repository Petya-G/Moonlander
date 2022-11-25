#ifndef LANDER_H
#define LANDER_H
#include "geometry.h"
#include "level.h"
#include "score.h"
#include "sdlstuff.h"

typedef struct Lander {
  Point pos;      // pozíció
  Point vel;      // sebesség, vektor(függőleges, vízszintes)
  int angle;      // dőlési szög
  int fuel;       // üzemanyag
  Uint32 elapsed; // mennyi ideig repül
} Lander;

extern const float g;
extern Line landerLines[];
void updateLander(Lander *lander, Line landerLines[]);
void landerEvent(Lander *lander, SDL_Event event, double dt);
Lander landerReset();
#endif