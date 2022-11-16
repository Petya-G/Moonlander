#include "debugmalloc.h"
#include "geometry.h"
#include "lander.h"
#include "level.h"
#include "sdlstuff.h"
#include "text.h"
#include <stdlib.h>

int main(int argc, char *arg[]) {
  if (!init())
    exit(1);

  Uint32 lastTick = SDL_GetTicks();
  elapsed = SDL_GetTicks();
  
  initTerrain(450, 200);
  generateTerrain();

  SDL_Event event;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        quit = true;

      Uint32 curTick = SDL_GetTicks();
      double dt = (curTick - lastTick) / 1000.0;
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