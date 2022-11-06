#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <math.h>
#include <stdbool.h>
#include "sdlstuff.h"

#define TORAD(angle) (M_PI * angle / 180.0)

typedef struct Point {
  float x;
  float y;
} Point;

typedef struct Line {
  Point a;
  Point b;
} Line;

Point rotatePoint(Point p, Point o, float angle);
Line rotateLine(Line l, Point o, float angle);
void renderLine(Line l);
#endif