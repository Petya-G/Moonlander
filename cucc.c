#include "score.h"

int calculateScore(int fuel, Uint32 elapsed) { return fuel / elapsed; }

void renderScores(Score *scores, int total) {
  char str[100];
  for (int i = 0; i < total; ++i) {
    snprintf(str, sizeof(str), "%s %d", scores[i].name, scores[i].points);
    stringRGBA(renderer, 400, i * 12, str, 255, 255, 255, 255);
  }

  SDL_Delay(2000);
}

void updateScore(char name[], int points) {
  Score *scores;
  int total = 0;
  scores = readScores("scores.bin", &total);

  if (scores == NULL) {
    scores = (Score *)malloc(sizeof(Score));
    strcpy(scores[0].name, name);
    scores[0].points = points;
    writeScores("scores.bin", scores, 1);

    free(scores);
    return;
  }

  ++total;
  strcpy(scores[total].name, name);
  scores[total].points = points;

  sortScores(scores, total);
  writeScores("scores.bin", scores, total);
  renderScores(scores, total);
  free(scores);
}

void sortScores(Score *scores, int total) {
  int i, j;
  for (i = 0; i < total - 1; i++)
    for (j = 0; j < total - i - 1; j++)
      if (scores[j].points > scores[j + 1].points)
        swapScore(&scores[j], &scores[j + 1]);
}

void swapScore(Score *sc1, Score *sc2) {
  Score temp = *sc1;
  *sc1 = *sc2;
  *sc2 = temp;
}

Score *readScores(char *filename, int *total) {
  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL)
    return NULL;

  if (fread(total, sizeof(int), 1, file) != 1)
    return NULL;

  Score *scores = malloc(sizeof(Score) * (*total + 1));
  if (fread(scores, sizeof(Score), *total, file) != *total) {
    free(scores);
    return NULL;
  }

  if (fclose(file) == EOF) {
    free(scores);
    return NULL;
  }

  return scores;
}

bool writeScores(char *filename, Score *scores, int total) {
  FILE *file;
  file = fopen(filename, "wb");

  if (file == NULL)
    return false;

  if (fwrite(&total, sizeof(int), 1, file) != 1)
    return false;

  if (fwrite(scores, sizeof(Score), total, file) != total)
    return false;

  if (fclose(file) == EOF)
    return false;

  return true;
}

#ifndef SCORE_H
#define SCORE_H
#include "debugmalloc.h"
#include "sdlstuff.h"
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[30];
  int points;
} Score;

int calculateScore(int fuel, Uint32 elapsed);
void updateScore(char name[], int points);
bool writeScores(char *filename, Score *scores, int total);
Score *readScores(char *filename, int *total);
void sortScores(Score *scores, int total);
void swapScore(Score *sc1, Score *sc2);

void renderScores(Score *scores, int total);
#endif