#include "lander.h"
#include <SDL2/SDL_rect.h>

const float g = 0.0116;

const int STARTVEL = 1;
Lander lander = {640 / 2.0, 480 / 2.0, 0, STARTVEL, STARTVEL};

void updateLander(void) {
  float x = lander.x;
  float y = lander.y;
  int n = 17;
  Point o = {lander.x, lander.y - 14};

  Line landerLines[] = {{{x + 13, y}, {x + 18, y}},
                        {{x - 12, y}, {x - 17, y}},
                        {{x + 15, y - 1}, {x + 10, y - 10}},
                        {{x - 14, y - 1}, {x - 9, y - 10}},
                        {{x - 10, y - 10}, {x + 12, y - 10}},
                        {{x - 10, y - 14}, {x + 12, y - 14}},
                        {{x - 10, y - 14}, {x - 10, y - 10}},
                        {{x + 12, y - 14}, {x + 12, y - 10}},
                        {{x - 3, y - 14}, {x + 4, y - 14}}, // octa
                        {{x + 4, y - 14}, {x + 9, y - 19}},
                        {{x + 9, y - 19}, {x + 9, y - 26}},
                        {{x + 9, y - 26}, {x + 9, y - 19}},
                        {{x + 9, y - 26}, {x + 4, y - 31}},
                        {{x + 4, y - 31}, {x - 3, y - 31}},
                        {{x - 3, y - 31}, {x - 8, y - 26}},
                        {{x - 8, y - 26}, {x - 8, y - 19}},
                        {{x - 3, y - 14}, {x - 8, y - 19}}};

  for (int i = 0; i < n; ++i) {
    Line rl = rotateLine(landerLines[i], o, lander.angle);
    landerLines[i] = rl;
  }

  bool landerCrash = false;
  for (int i = 0; i < n; ++i) {
    if (intersect(landerLines[i], l[0]))
      landerCrash = true;
  }

  if (landerCrash) {
    lander.y = HEIGHT / 2.0;
    lander.x = WIDTH / 2.0;
    lander.xvel = STARTVEL;
    lander.yvel = STARTVEL;
  }

  else {
    if (lander.xvel > 0)
      lander.xvel -= g / 100;
    else if (lander.xvel < 0)
      lander.xvel += g / 100;

    lander.yvel += g;
    lander.x += lander.xvel;
    lander.y += lander.yvel;
  }

  for (int i = 0; i < n; ++i)
    renderLine(landerLines[i]);
}

void landerEvent(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
      lander.yvel -= 0.5 * sin(M_PI * (lander.angle + 90.0) / 180.0);
      lander.xvel -= 0.5 * cos(M_PI * (lander.angle + 90.0) / 180.0);
    }

    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      lander.angle -= 5;

    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      lander.angle += 5;

    if (lander.angle == 360 || lander.angle == -360)
      lander.angle = 0;
  }
}