#include "lander.h"

const float g = 0.0116;

const int STARTVEL = 1;
Lander lander = {640.0 / 8, 480.0 / 8, 0, STARTVEL, STARTVEL, 600};
Uint32 elapsed;

void landerUpdate(void) {
  float x = lander.x;
  float y = lander.y;
  int n = 17;
  Point o = {lander.x, lander.y - 14};

  Line landerLines[] = {{{x + 13, y}, {x + 18, y}}, // láb
                        {{x - 12, y}, {x - 17, y}}, // láb
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
  bool landed = false;
  for (int i = 0; i < n; ++i) {
    for (Segment *k = tail; k != NULL; k = k->next) {
      if (k->flat && intersect(landerLines[i], k->l) && lander.angle == 0)
        landed = true;
      else if (intersect(landerLines[i], k->l))
        landerCrash = true;
    }
  }

  if (landed) {
    SDL_Delay(1000);
    landed = false;
    landerReset();
  }

  else if (landerCrash)
    landerReset();

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

void landerReset() {
  lander.y = HEIGHT / 8.0;
  lander.x = WIDTH / 8.0;
  lander.xvel = STARTVEL;
  lander.yvel = STARTVEL;
  lander.fuel = 300;
  elapsed = SDL_GetTicks();
}

void landerEvent(SDL_Event event, double dt) {
  if (event.type == SDL_KEYDOWN) {
    if (lander.fuel >= 0 &&
        (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)) {
      lander.yvel -= 0.03 * sin(M_PI * (lander.angle + 90.0) / 180.0) * dt;
      lander.xvel -= 0.03 * cos(M_PI * (lander.angle + 90.0) / 180.0) * dt;
      lander.fuel -= 1 * dt;
    }

    if (lander.fuel < 0)
      lander.fuel = 0;

    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      lander.angle -= 5;

    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      lander.angle += 5;

    if (lander.angle == 360 || lander.angle == -360)
      lander.angle = 0;
  }
}