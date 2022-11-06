#include "text.h"

void renderText(void) {
  char str[50];
  snprintf(str, sizeof(str), "Altidue: %lf", HEIGHT - lander.y);
  stringRGBA(renderer, 0, 0, str, 255, 255, 255, 255);
  snprintf(str, sizeof(str), "Horizontal Speed: %lf", lander.xvel);
  stringRGBA(renderer, 0, 12, str, 255, 255, 255, 255);
  snprintf(str, sizeof(str), "Vertical Speed: %lf", lander.yvel);
  stringRGBA(renderer, 0, 24, str, 255, 255, 255, 255);
  snprintf(str, sizeof(str), "angle: %lf", lander.angle);
  stringRGBA(renderer, 0, 36, str, 255, 255, 255, 255);
}