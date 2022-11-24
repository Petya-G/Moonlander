#include "geometry.h"

//https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
bool ccw(Point a, Point b, Point c) {
  return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

//Vonalak metszik e egymást
bool intersect(Line l1, Line l2) {
  return ccw(l1.a, l2.a, l2.b) != ccw(l1.b, l2.a, l2.b) &
         ccw(l1.a, l1.b, l2.a) != ccw(l1.a, l1.b, l2.b);
}

//Pontot egy szöggel forgat egy másik pont körül
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

//Vonalat megforgat egy szöggel egy pont körül
Line rotateLine(Line l, Point o, float angle) {
  Line rl = {rotatePoint(l.a, o, angle), rotatePoint(l.b, o, angle)};
  return rl;
}

//Vonalt kicsinyít, nagyít
Line scaleLine(Line l, float scalar) {
  l.a.x = l.a.x * scalar;
  l.a.y = l.a.y * scalar;
  l.b.x = l.b.x * scalar;
  l.b.y = l.b.y * scalar;
  return l;
}

//Vonalat elmozgat
Line moveLine(Line l, Point p) {
  l.a.x += p.x;
  l.a.y += p.y;
  l.b.x += p.x;
  l.b.y += p.y;
  return l;
}

//Vonalt megjelenít, fehéren
void renderLine(Line l) {
  aalineRGBA(renderer, l.a.x, l.a.y, l.b.x, l.b.y, 255, 255, 255, 255);
}