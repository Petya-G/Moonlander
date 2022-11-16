#include "level.h"

Segment *tail;
Segment *head;
const float n = 5.0;
float step = 640.0 / n;

void generateTerrain() {
  srand(time(NULL));
  for (int i = 0; i < n; ++i) {
    int y = 50 + rand() % 430;
    if (i % 5 == 0)
      append(y, true);
    else
      append(y, false);
  }
}

void append(float y, bool flat) {
  Segment *new = (Segment *)malloc(sizeof(Segment));

  new->prev = head;
  new->next = NULL;
  new->l.a.x = head->l.b.x;
  new->l.a.y = head->l.b.y;
  new->l.b.x = head->l.b.x + step;

  new->flat = flat;
  if (flat)
    new->l.b.y = head->l.b.y;
  else
    new->l.b.y = y;

  head->next = new;
  head = new;
  return;
}

void initTerrain(float start, float end) {
  tail = (Segment *)malloc(sizeof(Segment));
  head = (Segment *)malloc(sizeof(Segment));

  tail->prev = NULL;
  tail->next = head;
  tail->l.a.x = 0;
  tail->l.a.y = HEIGHT;
  tail->l.b.x = step;
  tail->l.b.y = start;
  tail->flat = false;

  head->prev = tail;
  head->next = NULL;
  head->l.a.x = head->prev->l.b.x;
  head->l.a.y = head->prev->l.b.y;
  head->l.b.x = head->l.a.x + step;
  head->l.b.y = end;
  head->flat = false;
}

void renderTerrain() {
  for (Segment *i = tail; i != NULL; i = i->next)
    renderLine(i->l);
}

void freeTerrain() {
  Segment *i;
  i = tail;
  while (i != NULL) {
    Segment *next = i->next;
    free(i);
    i = next;
  }
}