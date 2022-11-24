#include "lander.h"
#include "level.h"

// Gravitácós állandó
const float g = 1.16;
const int STARTVEL = 200;

void updateLander(Lander *lander, Line landerLines[]) {
  // Végig megy a vonalakon
  Point o = {lander->pos.x, lander->pos.y - 14};
  for (int i = 0; i < 17; ++i) {
    // Frissíti a pozicójukat
    landerLines[i] = moveLine(landerLines[i], lander->pos);
    // A dőlési szögüket, a lander közepéhez alulrók képest
    landerLines[i] = rotateLine(landerLines[i], o, lander->angle);
    // túl nagyra definiáltam a vonalakat, ezért zsugorítja
    landerLines[i] = scaleLine(landerLines[i], 0.5);
  }

  // kirajzoljuk
  for (int i = 0; i < 17; ++i)
    renderLine(landerLines[i]);
}

Lander landerReset() {
  Lander lander;
  lander.pos.x = 40;
  lander.pos.y = 40;
  lander.vel.x = STARTVEL;
  lander.vel.y = 0;
  lander.angle = 0;
  lander.fuel = 300;
  lander.elapsed = SDL_GetTicks();
  return lander;
}

void landerEvent(Lander *lander, SDL_Event event, double dt) {
  if (event.type == SDL_KEYDOWN) {
    // w/fel gombok lenyomására, ha van üzemanyag
    if (lander->fuel >= 0 && event.key.keysym.sym == SDLK_UP ||
        lander->fuel >= 0 && event.key.keysym.sym == SDLK_w) {
      // nem vagyok nagy fizikus
      const int speed = 300;
      lander->vel.y -= speed * sin(M_PI * (lander->angle + 90.0) / 180.0) * dt;
      lander->vel.x -= speed * cos(M_PI * (lander->angle + 90.0) / 180.0) * dt;
      lander->fuel -= 1 * dt;
    }

    // lander szög
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      lander->angle -= 5;

    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      lander->angle += 5;

    if (lander->angle == 360 || lander->angle == -360)
      lander->angle = 0;
  }
}