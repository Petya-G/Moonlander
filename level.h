#ifndef LEVEL_H
#define LEVEL_H
#include "geometry.h"
#include "sdlstuff.h"
#include "debugmalloc.h"
#include <stdlib.h>
#include <time.h>

typedef struct Segment {
  Line line;
  bool flat;
  struct Segment *prev;
  struct Segment *next;
} Segment;

typedef struct Level {
  Segment *tail;
  Segment *head;
  Point pos;
} Level;

Level *initLevel(float start, float end);
void generateLevel(Level *level);
void append(Level *level, float y, bool flat);
void renderLevel(Level *level);
void freeLevel(Level *level);
Level *resetLevel(Level *level);
#endif