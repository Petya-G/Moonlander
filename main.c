#include "debugmalloc.h"
#include "sdlstuff.h"
#include "geometry.h"
#include "lander.h"
#include "level.h"
#include "text.h"

void landerEvent(SDL_Event event);

int main(int argc, char *arg[]) {
  if (!init())
    exit(1);

  bool quit = false;
  SDL_Event event;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        quit = true;

      landerEvent(event);
    }
    update();
  }

  shutdown();
}

void update(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  updateLander();

  renderLander();
  renderLevel();
  renderText();

  SDL_RenderPresent(renderer);
}