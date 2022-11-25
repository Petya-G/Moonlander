#include "score.h"

// ezen a képlet alapján számítja ki a szerzett pontot
int calculateScore(int fuel, Uint32 elapsed) {
  return 100 + 200 / elapsed + fuel;
}

void updateScore(int score) {
  FILE *file;
  int hscores[11] = {0}; // inicalizáljuk nullákkal

  // score.txt-be fogunk írni/olvasni
  file = fopen("score.txt", "r");

  // ha létezik a fájl beolvassuk a highscores-ba
  if (file != NULL)
    for (int i = 0; i < 10; ++i)
      fscanf(file, "%d\n", &hscores[i]);
  fclose(file);

  hscores[10] = score; // utolsó a score lesz

  //rendezzük a highscores-t, legnagyobb legelőre
  for (int i = 0; i < 11 - 1; i++) {
    for (int j = 0; j < 11 - i - 1; j++) {
      if (hscores[j] < hscores[j + 1]) {
        int temp = hscores[j];
        hscores[j] = hscores[j + 1];
        hscores[j + 1] = temp;
      }
    }
  }

  // az első tizet visszaírjuk a fájlba, utolsót elhagyjuk
  file = fopen("score.txt", "w");
  for (int i = 0; i < 10; i++)
    fprintf(file, "%d\n", hscores[i]);
  fclose(file);
}