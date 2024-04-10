#ifndef BOMB_H
#define BOMB_H

#include "block.h"
#include "player.h"



typedef struct Bomb {
    Position position;
    ALLEGRO_BITMAP* graphic;
    int power;
    float time;
    struct Bomb* next; // Nastepna bomba
    Player* owner; // wlasciciel bomby
} Bomb;


// FUKCJE
void initBomb(Bomb* bomb, int x, int y, int power, float time,  Player* owner);
bool addBomb(Bomb** head, int x, int y, int power, float time,  Player* owner);
void drawBombs(Bomb* head, ALLEGRO_DISPLAY* display);
void timerBomb(Bomb** bomb, Block* blocks, Player* players, int playerNumber);


#endif /* BOMB_H */