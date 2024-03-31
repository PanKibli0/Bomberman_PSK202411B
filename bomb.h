#ifndef BOMB_H
#define BOMB_H

#include "position.h"

typedef struct Bomb {
    Position position;
    ALLEGRO_BITMAP* bombGraphic;
    int power;
    float time;
    struct Bomb* next; // Nastepna bomba
} Bomb;

typedef struct {
	Position position;
	ALLEGRO_BITMAP* playerGraphic;
	int direction;
} Explode;

// FUKCJE

void initBomb(Bomb* bomb, int x, int y, int power, float time);
bool addBomb(Bomb** head, int x, int y, int power, float time);
void drawBombs(Bomb* head, ALLEGRO_DISPLAY* display);
void timerBomb(Bomb** bomb);


#endif /* BOMB_H */