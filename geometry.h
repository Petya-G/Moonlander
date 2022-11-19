#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "sdlstuff.h"
#include <math.h>
#include <stdbool.h>

#define TORAD(angle) (M_PI * angle / 180.0)

typedef struct Point {
  float x;
  float y;
} Point;

typedef struct Line {
  Point a;
  Point b;
} Line;

bool ccw(Point a, Point b, Point c);
bool intersect(Line l1, Line l2);
Point rotatePoint(Point p, Point o, float angle);
Line rotateLine(Line l, Point o, float angle);
Line scaleLine(Line l, float scalar);
Line moveLine(Line l, Point a);
bool linesInstersect(Line l1, Line l2);
void renderLine(Line l);
#endif