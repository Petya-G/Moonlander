#include "level.h"
#include "geometry.h"

int n = 1;
Line l[] = {{{0, 300}, {640, 300}}};
void renderLevel(void) {
  for(int i = 0; i < n; ++i)
    renderLine(l[i]);
}