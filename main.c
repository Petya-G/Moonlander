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

  // mennyi idő telik el
  elapsed = SDL_GetTicks();
  Uint32 lastTick = SDL_GetTicks();

  // Pálya generálás, első két elem előre megadott
  initTerrain(450, 430);
  generateTerrain();

  SDL_Event event;
  bool quit = false;

  // Main loop
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        quit = true;

      // Mennyi idő telt el az előző frame óta
      Uint32 curTick = SDL_GetTicks();
      double dt = (curTick - lastTick) / 1000.0;
      lastTick = curTick;
      landerEvent(event, dt);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    landerUpdate();
    renderTerrain();
    renderText();

    SDL_RenderPresent(renderer);
  }
  freeTerrain();
  shutdown();
  return 0;
}