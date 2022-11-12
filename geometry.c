#include "geometry.h"

bool ccw(Point a, Point b, Point c){
  return (c.y-a.y)*(b.x-a.x) > (b.y-a.y)*(c.x-a.x);
}

bool intersect(Line l1, Line l2){
  return ccw(l1.a,l2.a,l2.b) != ccw(l1.b,l2.a,l2.b) & ccw(l1.a,l1.b,l2.a) != ccw(l1.a,l1.b,l2.b);
}

Point rotatePoint(Point p, Point o, float angle) {
  float c = cos(TORAD(angle));
  float s = sin(TORAD(angle));

  Point p2;
  float x = p.x - o.x;
  float y = p.y - o.y;
  p2.x = c * x - s * y + o.x;
  p2.y = s * x + c * y + o.y;

  return p2;
}

Line rotateLine(Line l, Point o, float angle) {
  Line rl = {rotatePoint(l.a, o, angle), rotatePoint(l.b, o, angle)};
  return rl;
}

void renderLine(Line l) {
  aalineRGBA(renderer, l.a.x, l.a.y, l.b.x, l.b.y, 255, 255, 255, 255);
}