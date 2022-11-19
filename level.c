#include "level.h"

Terrain *terrain;

// hány részből álljon a pálya
const float n = 30.0;
// horizontális nagysága a pályaelemnek
float step = 640 / n;

void generateTerrain() {
  // előző pályaelem magassága
  int prev = terrain->head->l.b.y;
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
      append(y, true);
    else
      append(y, false);
    prev = y;
  }
}

// végére fűzünk új pályaelemet
void append(float y, bool flat) {
  Segment *new = (Segment *)malloc(sizeof(Segment));

  new->prev = terrain->head;
  new->next = NULL;
  new->l.a.x = terrain->head->l.b.x;
  new->l.a.y = terrain->head->l.b.y;
  new->l.b.x = new->l.a.x + step;

  new->flat = flat;
  // ha lapos legyen a két pontja ugyan olyan magas
  if (flat)
    new->l.b.y = new->l.a.y;
  else
    new->l.b.y = y;

  terrain->head->next = new;
  terrain->head = new;
  return;
}

void initTerrain(float start, float end) {
  terrain = (Terrain *)malloc(sizeof(Terrain));
  Point pos = {0,0};
  terrain->pos = pos;
  
  Segment *tail;
  Segment *head;
  tail = (Segment *)malloc(sizeof(Segment));
  head = (Segment *)malloc(sizeof(Segment));
  terrain->tail = tail;
  terrain->head = head;

  terrain->tail->prev = NULL;
  terrain->tail->next = terrain->head;
  terrain->tail->l.a.x = 0;
  terrain->tail->l.a.y = HEIGHT;
  terrain->tail->l.b.x = step;
  terrain->tail->l.b.y = start;
  terrain->tail->flat = false;

  terrain->head->prev = tail;
  terrain->head->next = NULL;
  terrain->head->l.a.x = terrain->head->prev->l.b.x;
  terrain->head->l.a.y = terrain->head->prev->l.b.y;
  terrain->head->l.b.x = terrain->head->l.a.x + step;
  terrain->head->l.b.y = end;
  terrain->head->flat = false;
}

void renderTerrain() {
  for (Segment *i = terrain->tail; i != NULL; i = i->next)
    renderLine(i->l);
}

void freeTerrain() {
  Segment *i;
  i = terrain->tail;
  while (i != NULL) {
    Segment *next = i->next;
    free(i);
    i = next;
  }
}