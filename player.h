#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "bomb.h" 

typedef struct {
    int bombAmount;
    float bombTime;
    int BombPower;
} BombData;


typedef struct {
    Position position;
    ALLEGRO_BITMAP* playerGraphic;
    float velocity;
    BombData bombs;
    ALLEGRO_COLOR color;
    int controlKeys[5];
} Player;

// FUKCJE
void initPlayer(Player* player, int x, int y, int velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);
void drawPlayer(Player* player, ALLEGRO_DISPLAY* display);
void movePlayer(Player* player, ALLEGRO_KEYBOARD_STATE* keyState);
void placeBomb(Player* player, Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState);


#endif /* PLAYER_H */