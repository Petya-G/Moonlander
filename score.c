#include "score.h"

// ezen a képlet alapján számítja ki a szerzett pontot
int calculateScore(int fuel, Uint32 elapsed) {
  return 100 + 200 / elapsed + 100 * fuel;
}

void updateScore(int score) {
  FILE *file;
  int hscore;

  // score.txt-be fogunk írni/olvasni
  file = fopen("score.txt", "r");

  // ha létezik a fájl beolvassuk az elős sorban tárolt highscore-t
  if (file != NULL)
    fscanf(file, "%d", &hscore);

  // ha nem létezik akkor 0 a highscore
  else
    hscore = 0;
  fclose(file);

  // ha mostani score nagyobb a highscore-nál, beírjuk a fájlba
  if (score > hscore) {
    file = fopen("score.txt", "w");
    fprintf(file, "%d", score);
    fclose(file);
  }
}