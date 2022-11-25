#ifndef SCORE_H
#define SCORE_H
#include "debugmalloc.h"
#include "sdlstuff.h"
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculateScore(int fuel, Uint32 elapsed);
void updateScore(int points);

#endif