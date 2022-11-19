#include "lander.h"

// Gravitácós állandó
const float g = 0.0116;
const int STARTVEL = 1;
// ezt a landert használja a program mindenhol
Lander lander = {{0, 0}, 0, STARTVEL, STARTVEL, 300};
Uint32 elapsed;

void landerUpdate(void) {
  // Lander közepe alulról, e körül forgajta
  Point o = {lander.pos.x, lander.pos.y - 14};

  int size = 17;
  // Vonalak amikből felépül a lander
  Line landerLines[] = {{{+13, 0}, {+18, 0}}, // láb
                        {{-12, 0}, {-17, 0}}, // láb
                        {{+15, -1}, {+10, -10}},  {{-14, -1}, {-9, -10}},
                        {{-10, -10}, {+12, -10}}, {{-10, -14}, {+12, -14}},
                        {{-10, -14}, {-10, -10}}, {{+12, -14}, {+12, -10}},

                        {{-3, -14}, {+4, -14}}, // octagon
                        {{+4, -14}, {+9, -19}},   {{+9, -19}, {+9, -26}},
                        {{+9, -26}, {+9, -19}},   {{+9, -26}, {+4, -31}},
                        {{+4, -31}, {-3, -31}},   {{-3, -31}, {-8, -26}},
                        {{-8, -26}, {-8, -19}},   {{-3, -14}, {-8, -19}}};

  // Végig megy a vonalakon
  for (int i = 0; i < size; ++i) {
    // Frissíti a pozicójukat
    landerLines[i] = moveLine(landerLines[i], lander.pos);
    // A dőlési szögüket
    landerLines[i] = rotateLine(landerLines[i], o, lander.angle);
    // túl nagyra definiáltam a vonalakat, ezért zsugorítja
    landerLines[i] = scaleLine(landerLines[i], 0.5);
  }

  bool landerCrash = false;
  bool landed = false;

  // Hitdetection
  // lander és pálya vonailain végig megy
  for (int i = 0; i < size; ++i) {
    for (Segment *k = terrain->tail; k != NULL; k = k->next) {
      // metszik e egymást, lapos e és a dőlési szög 0
      if (intersect(landerLines[i], k->l) && k->flat && lander.angle == 0)
        landed = true;
      // metszik e egymást
      else if (intersect(landerLines[i], k->l))
        landerCrash = true;
    }
  }

  // landolt
  if (landed) {
    updateScore(calculateScore(lander.fuel, elapsed));
    SDL_Delay(1000);
    landed = false;
    landerReset();
  }

  // lezuhant
  else if (landerCrash)
    landerReset();

  // semmi nem történt
  else {
    // veszt xvel-ből amig nem nulla (légellenállás szerű)
    if (lander.xvel > 0)
      lander.xvel -= g / 100;
    else if (lander.xvel < 0)
      lander.xvel += g / 100;

    // gyorsul lefele
    lander.yvel += g;
    // frissítjuk a lander poizícióját
    lander.pos.x += lander.xvel;
    lander.pos.y += lander.yvel;
  }

  // kirajzoljuk
  for (int i = 0; i < size; ++i)
    renderLine(landerLines[i]);
}

void landerReset() {
  lander.pos.x = 0;
  lander.pos.y = 0;
  lander.xvel = STARTVEL;
  lander.yvel = STARTVEL;
  lander.fuel = 300;
  elapsed = SDL_GetTicks();
}

void landerEvent(SDL_Event event, double dt) {
  if (event.type == SDL_KEYDOWN) {
    // w/fel gombok lenyomására, ha van üzemanyag
    if (lander.fuel >= 0 && event.key.keysym.sym == SDLK_UP ||
        lander.fuel >= 0 && event.key.keysym.sym == SDLK_w) {
      // nem vagyok nagy fizikus
      lander.yvel -= 2 * sin(M_PI * (lander.angle + 90.0) / 180.0) * dt;
      lander.xvel -= 2 * cos(M_PI * (lander.angle + 90.0) / 180.0) * dt;
      lander.fuel -= 1 * dt;
    }

    // lander szög
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      lander.angle -= 5;

    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      lander.angle += 5;

    if (lander.angle == 360 || lander.angle == -360)
      lander.angle = 0;
  }
}