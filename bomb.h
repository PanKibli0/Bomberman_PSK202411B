#ifndef BOMB_H
#define BOMB_H

#include "position.h"
#include "block.h"

typedef struct Bomb {
    Position position;
    ALLEGRO_BITMAP* graphic;
    int power;
    float time;
    struct Bomb* next; // Nastepna bomba
    int owner; // Indeks wlasciciela bomby
} Bomb;


// FUKCJE

void initBomb(Bomb* bomb, int x, int y, int power, float time, int owner);
bool addBomb(Bomb** head, int x, int y, int power, float time, int owner);
void drawBombs(Bomb* head, ALLEGRO_DISPLAY* display);
int timerBomb(Bomb** bomb, Block* blocks);


#endif /* BOMB_H */