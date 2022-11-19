#include "score.h"

int calculateScore(int fuel, Uint32 elapsed) {
  return 100 + 1000 * (fuel / elapsed);
}

void renderScore(int score) {
  char str[100];
  snprintf(str, sizeof(str), "%d", score);
  stringRGBA(renderer, 400, 12, str, 255, 255, 255, 255);
  SDL_Delay(2000);
}

void updateScore(int score) {
  FILE *file;
  file = fopen("score.txt", "r+");
  int oldscore;

  fscanf(file, "%d", &oldscore);
  if (score > oldscore) {
    renderScore(score);
    fprintf(file, "%d", score);
  } else
    renderScore(oldscore);
}