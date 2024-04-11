#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "block.h"

struct Bomb;

typedef struct {
    int bombAmount;
    float bombTime;
    int BombPower;
} BombData;


typedef struct {
    unsigned int health;
    Position position;
    ALLEGRO_BITMAP* graphic;
    float velocity;
    BombData bombs;
    ALLEGRO_COLOR color;
    int controlKeys[5];
} Player;

// FUKCJE
void initPlayer(Player* player, unsigned int health, int x, int y, float velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);
void drawPlayer(Player* player,int playerNumber, ALLEGRO_DISPLAY* display);
void movePlayer(Player* player, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, struct Bomb* bomb);
void placeBomb(Player* players, int playerNumber, struct Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState);

#endif /* PLAYER_H */