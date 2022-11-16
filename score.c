#include "score.h"

int calculateScore() { return lander.fuel / time; }

void updateLeaderBoard() {
  FILE *fp;
  fp = fopen("score.txt", "r");
  if(fp == NULL){
    perror("file not found");
    return;
  }


}