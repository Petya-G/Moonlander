#include "sdlstuff.h"

const int WIDTH  = 640;
const int HEIGHT  = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "init: %s", SDL_GetError());
    return false;
  }

  window =
      SDL_CreateWindow("Moonlander", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  SDL_ShowWindow(window);
  if (!window) {
    fprintf(stderr, "window: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    fprintf(stderr, "renderer: %s", SDL_GetError());
    return false;
  }

  return true;
}

void shutdown(void) {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  window = NULL;
  renderer = NULL;

  SDL_Quit();
}