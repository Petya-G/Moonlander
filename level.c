#include "level.h"
#include "geometry.h"

Level *level;

// hány részből álljon a pálya
const float n = 30.0;
// hossza a pályaelemnek
float step = 640 / n;

// egy képernyő hosszával megegyező pályarészt generál
void generateLevel(Level *level) {
  // előző pályaelem magassága
  int prev = level->head->line.b.y;
  for (int i = 0; i < n; ++i) {
    int y;
    do {
      // fentebb, vagy lejebb lesz a köv. pályaelem az előzőhöz
      if (rand() % 2)
        y = prev + rand() % 50;
      else
        y = prev - rand() % 50;
      // out of bounds ne legyen
    } while (y < 0 || y > HEIGHT);

    // minden ötödik lapos
    if (i % 5 == 0)
      append(level, y, true);
    else
      append(level, y, false);
    prev = y;
  }
}

// végére fűzünk új pályaelemet
void append(Level *level, float y, bool flat) {
  Segment *new = (Segment *)malloc(sizeof(Segment));

  new->prev = level->head;
  new->next = NULL;
  new->line.a.x = level->head->line.b.x;
  new->line.a.y = level->head->line.b.y;
  new->line.b.x = new->line.a.x + step;

  new->flat = flat;
  // ha lapos legyen a két pontja ugyan olyan magas
  if (flat)
    new->line.b.y = new->line.a.y;
  else
    new->line.b.y = y;

  level->head->next = new;
  level->head = new;
  return;
}

Level *initLevel(float start, float end) {
  level = (Level *)malloc(sizeof(Level));
  // 0 a pozíciója
  Point pos = {0, 0};
  level->pos = pos;

  // előre lefoglaljuk az elejét és a végét
  Segment *tail;
  Segment *head;
  tail = (Segment *)malloc(sizeof(Segment));
  head = (Segment *)malloc(sizeof(Segment));
  level->tail = tail;
  level->head = head;

  // eleje
  level->tail->prev = NULL;
  level->tail->next = level->head;
  // 0,0-nál kezd
  level->tail->line.a.x = 0;
  level->tail->line.a.y = HEIGHT;
  // egy pályaelem hosszú és start elem magas
  level->tail->line.b.x = step;
  level->tail->line.b.y = start;
  level->tail->flat = false;

  level->head->prev = tail;
  level->head->next = NULL;
  // az első pontja az előző második pontja
  level->head->line.a.x = level->head->prev->line.b.x;
  level->head->line.a.y = level->head->prev->line.b.y;
  // az x-e az előző pont + egy pályaelem hossza, az y end magas
  level->head->line.b.x = level->head->line.a.x + step;
  level->head->line.b.y = end;
  level->head->flat = false;
  return level;
}

Level *reset(Level *level) {
  // felszabadítjuk a pályát
  freeLevel(level);

  // létrehozzuk és inicalizáljuk az új pálytá
  Level *temp;
  temp = initLevel(450, 430);

  // 50 width méretű elemet generál, remélhetőleg ezeken belül marad
  for (int i = 0; i < 50; ++i)
    generateLevel(temp);
  return temp;
}

void renderLevel(Level *level) {
  for (Segment *i = level->tail; i != NULL; i = i->next) {
    Line l;
    l = moveLine(i->line, level->pos);
    renderLine(l);
  }
}

void freeLevel(Level *level) {
  Segment *i;
  i = level->tail;
  while (i != NULL) {
    Segment *next = i->next;
    free(i);
    i = next;
  }
}