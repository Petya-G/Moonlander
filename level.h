#ifndef LEVEL_H
#define LEVEL_H
#include "geometry.h"
#include "sdlstuff.h"
#include <stdlib.h>
#include <time.h>

typedef struct Segment {
  Line l;
  bool flat;
  struct Segment *prev;
  struct Segment *next;
} Segment;

typedef struct Terrain {
  Segment *tail;
  Segment *head;
  Point pos;
} Terrain;

extern Terrain *terrain;
void generateTerrain();
void initTerrain(float start, float end);
void append(float y, bool flat);
void renderTerrain();
void freeTerrain();
#endif