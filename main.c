#include "debugmalloc.h"
#include "geometry.h"
#include "lander.h"
#include "level.h"
#include "score.h"
#include "sdlstuff.h"
#include "text.h"
#include <stdlib.h>

int main(int argc, char *arg[]) {
  // Inicializálja az sdlt
  if (!init())
    exit(1);
  srand(time(NULL));

  // Lander változó
  Lander *lander;
  Lander lndr = landerReset();
  lander = &lndr;

  // Pálya generálás, első két elem előre megadott
  Level *level;
  level = initLevel(450, 430);
  for (int i = 0; i < 30; ++i)
    generateLevel(level);

  SDL_Event event;
  bool quit = false;
  double dt;

  // Main loop
  Uint32 lastTick = SDL_GetTicks();
  while (!quit) {
    // Mennyi idő telt el az előző frame óta
    Uint32 curTick = SDL_GetTicks();
    dt = (curTick - lastTick) / 1000.0;
    lastTick = curTick;

    // eventkezelő
    while (SDL_PollEvent(&event)) {
      // addig fut a program ameddig ki nem lépünk
      if (event.type == SDL_QUIT)
        quit = true;

      landerEvent(lander, event, dt);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // a lander vonalai
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

    updateLander(lander, landerLines);

    // Hitdetection
    bool landerCrash = false;
    bool landed = false;

    // pálya szélei
    Line left = {{0, 0}, {0, HEIGHT}};
    Line top = {{0, 0}, {WIDTH, 0}};

    // lander és pálya vonailain végig megy
    for (int i = 0; i < 17; ++i) {
      for (Segment *k = level->tail; k != NULL; k = k->next) {
        Line l;
        l = moveLine(k->line, level->pos);

        // a lander metszik e egy lapos pályaelemet és a dőlési szöge 0
        if (intersect(landerLines[i], l) && k->flat && lander->angle == 0)
          landed = true;

        // más eseteben vagy ha outofbounds akkor
        else if (intersect(landerLines[i], l) ||
                 intersect(landerLines[i], left) ||
                 intersect(landerLines[i], top))
          landerCrash = true;
      }
    }

    // landolt
    if (landed) {
      updateScore(calculateScore(lander->fuel, lander->elapsed));
      SDL_Delay(1000);
      lndr = landerReset();
      level = reset(level);
    }

    // lezuhant
    else if (landerCrash) {
      lndr = landerReset();
      level = reset(level);
    }

    // nem ütközik
    else {
      // veszt vel.x-ből amig nem nulla (légellenállás szerű)
      if (lander->vel.x > 0)
        lander->vel.x -= g / 10 * dt;
      else if (lander->vel.x < 0)
        lander->vel.x += g / 10 * dt;
      // gyorsul lefele
      lander->vel.y += g;

      // frissítjuk a lander poizícióját
      lander->pos.y += lander->vel.y * dt;

      // a landert mozgatjuk ha nem értük el a pálya szélét, vagy visszafele gyorsul
      if (lander->vel.x < 0 || lander->pos.x < WIDTH * 2 - WIDTH * 0.25)
        lander->pos.x += lander->vel.x * dt;

      // a pályát mozgatjuk ha elértük a páyla szélét
      else if (lander->pos.x > WIDTH * 2 - WIDTH * 0.25) {
        level->pos.x -= lander->vel.x * dt;
      }
    }

    renderLevel(level);
    renderText(lander);

    SDL_RenderPresent(renderer);
  }
  freeLevel(level);
  shutdown();
  return 0;
}