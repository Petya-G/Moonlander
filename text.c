#include "text.h"

void renderText(Lander *lander) {
  char str[100]; // buffer

  //kiírjuk az adatokat egymás alá
  snprintf(str, sizeof(str), "Altidue: %.2f", HEIGHT * 2 - lander->pos.y);
  stringRGBA(renderer, 0, 0, str, 255, 255, 255, 255);

  snprintf(str, sizeof(str), "Horizontal Speed: %.2f", lander->vel.x);
  stringRGBA(renderer, 0, 12, str, 255, 255, 255, 255);

  snprintf(str, sizeof(str), "Vertical Speed: %.2f", lander->vel.y);
  stringRGBA(renderer, 0, 24, str, 255, 255, 255, 255);

  snprintf(str, sizeof(str), "Fuel: %03d", lander->fuel);
  stringRGBA(renderer, 0, 36, str, 255, 255, 255, 255);

  Uint32 curr = SDL_GetTicks();
  //eltelt időt kiírjuk mm:ss formátumba
  snprintf(str, sizeof(str), "Time: %02d:%02d", ((curr - lander->elapsed) / 1000) / 60, ((curr - lander->elapsed) / 1000) % 60);
  stringRGBA(renderer, 0, 48, str, 255, 255, 255, 255);
}