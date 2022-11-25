#include "debugmalloc.h"
#include "geometry.h"
#include "lander.h"
#include "level.h"
#include "score.h"
#include "sdlstuff.h"
#include "text.h"
#include <stdlib.h>

int main(int argc, char *arg[]) {
  // Inicializálja az sdlt, ha valami hiba történt kilép errror kóddal
  if (!init())
    exit(1);

  // Lander változó
  Lander *lander;
  Lander lndr = landerReset();
  lander = &lndr;

  // Pálya generálás, első két elem előre megadott
  Level *level;
  level = initLevel(450, 430);
  for (int i = 0; i < 10; ++i)
    generateLevel(level);

  Uint32 lastTick = SDL_GetTicks(); // előző frame ideje

  // game loop
  bool quit = false;
  while (!quit) {
    double dt; // delta time, mennyi idő telt el az előző frame óta
    Uint32 curTick = SDL_GetTicks();    // jelenlegi frame ideje
    dt = (curTick - lastTick) / 1000.0; // differenciájuk (ms-ba)
    lastTick = curTick;

    // eventkezelő
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      // addig fut a program ameddig ki nem lépünk
      if (event.type == SDL_QUIT)
        quit = true;

      landerEvent(lander, event, dt);
    }

    // feketére állítjuk a színt és az előző frame-ből maradt dolgokat töröljük
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

    // frissítjük a landert és kirajzoljuk
    updateLander(lander, landerLines);

    // pálya szélei
    Line left = {{0, 0}, {0, HEIGHT}};
    Line top = {{0, 0}, {WIDTH, 0}};

    // Hitdetection
    bool crashed = false;
    bool landed = false;
    // lander és pálya vonailain végig megy
    for (int i = 0; i < 17; ++i) {
      for (Segment *k = level->tail; k != NULL; k = k->next) {
        Line l = moveLine(k->line, level->pos);

        // lander lapos elemet metsz, dőlési szöge 5 fokon belül
        // van, x és y sebességének nagysága nem nagyobb 30-nál
        if (intersect(landerLines[i], l) && k->flat && abs(lander->angle) < 5 &&
            abs(lander->vel.x) < 60 && abs(lander->vel.y) < 60)
          landed = true;

        // más eseteben vagy ha outofbounds akkor
        else if (intersect(landerLines[i], l) ||
                 intersect(landerLines[i], left) ||
                 intersect(landerLines[i], top))
          crashed = true;
      }
    }

    // landolt
    if (landed) {
      // frissítjük a pontot
      updateScore(calculateScore(lander->fuel, lander->elapsed));
      SDL_Delay(2000);
      // resetelünk mindent
      lndr = landerReset();
      level = resetLevel(level);
    }

    // lezuhant, resetelünk mindent
    else if (crashed) {
      lndr = landerReset();
      level = resetLevel(level);
    }

    // nem ütközik
    else {
      // veszt vel.x-ből amig nem nulla (légellenállás szerű)
      if (lander->vel.x > 0)
        lander->vel.x -= g / 5 * dt;
      else if (lander->vel.x < 0)
        lander->vel.x += g / 5 * dt;
      // gyorsul lefele
      lander->vel.y += g * dt;

      // frissítjuk a lander poizícióját
      lander->pos.y += lander->vel.y * dt;

      // a landert mozgatjuk ha nem értük el a pálya szélét, vagy visszafele
      // gyorsul
      if (lander->vel.x < 0 || lander->pos.x < WIDTH * 2 - WIDTH * 0.33)
        lander->pos.x += lander->vel.x * dt;

      // a pályát mozgatjuk ha elértük a páyla szélét
      else if (lander->pos.x > WIDTH * 2 - WIDTH * 0.33) {
        level->pos.x -= lander->vel.x * dt;
      }
    }

    // kirajzoljuk a pályát, megjelenítjük a szöveget
    renderLevel(level);
    renderText(lander);

    // megjelenítjük az ablakba a fentieket
    SDL_RenderPresent(renderer);
  }
  // amikor kilép a program felszabadíjuk a pályát és az sdl-hez tartozó
  // dolgokat
  freeLevel(level);
  shutdown();
}