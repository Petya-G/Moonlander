#include "sdlstuff.h"

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "init: %s", SDL_GetError());
    return false;
  }

  window =
      SDL_CreateWindow("Moonlander", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  if (NULL == window) {
    fprintf(stderr, "window: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (NULL == renderer) {
    fprintf(stderr, "renderer: %s", SDL_GetError());
    return false;
  }

  return true;
}

void shutdown(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;
}