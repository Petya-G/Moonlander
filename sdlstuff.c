#include "sdlstuff.h"

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init() {

  bool success = true;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Initialization error: %s", SDL_GetError());
    success = false;
  } else {
    // Ablak letrehozasa
    window =
        SDL_CreateWindow("NHZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window creation error: %s", SDL_GetError());
      success = false;
    } else {
      // Renderer letrehozasa
      renderer = SDL_CreateRenderer(
          window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (renderer == NULL) {
        printf("Renderer could not be created!: %s", SDL_GetError());
        success = false;
      } 
    }
  }

  return success;

  // if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
  //   fprintf(stderr, "init: %s", SDL_GetError());
  //   return false;
  // }

  // window =
  //     SDL_CreateWindow("Moonlander", SDL_WINDOWPOS_CENTERED,
  //                      SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  // if (NULL == window) {
  //   fprintf(stderr, "window: %s", SDL_GetError());
  //   return false;
  // }

  // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  // if (NULL == renderer) {
  //   fprintf(stderr, "renderer: %s", SDL_GetError());
  //   return false;
  // }

  // return true;
}

void shutdown(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;
}