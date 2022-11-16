#include "text.h"

void renderText(void) {
  char str[100];
  snprintf(str, sizeof(str), "Altidue: %.2f", HEIGHT - lander.y);
  stringRGBA(renderer, 0, 0, str, 255, 255, 255, 255);
  snprintf(str, sizeof(str), "Horizontal Speed: %.2f", lander.xvel);
  stringRGBA(renderer, 0, 12, str, 255, 255, 255, 255);
  snprintf(str, sizeof(str), "Vertical Speed: %.2f", lander.yvel);
  stringRGBA(renderer, 0, 24, str, 255, 255, 255, 255);
  snprintf(str, sizeof(str), "Fuel: %03d", lander.fuel);
  stringRGBA(renderer, 0, 36, str, 255, 255, 255, 255);
  Uint32 curr = SDL_GetTicks();
  snprintf(str, sizeof(str), "Time: %02d:%02d", ((curr - elapsed) / 1000) / 60, ((curr - elapsed) / 1000) % 60);
  stringRGBA(renderer, 0, 48, str, 255, 255, 255, 255);
}