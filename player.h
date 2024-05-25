#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "block.h"


struct Bomb;

typedef struct {
    int bombAmount;
    float bombTime;
    int BombPower;
} BombData;

typedef struct {
    bool kick; // Kopanie bomb
    struct {  bool active; bool hold; } bombThief; // wziecie postawionej bomby
    bool randomTeleport; // losowa zmiana miejsca 
    float invisibility; //  niewidzialnosc
    /*V*/ float shieldTime; // chroni przed obrazeniami
} PowerUpData;


typedef struct {
    int health;
    Position position;
    ALLEGRO_BITMAP* graphic;
    float velocity;
    BombData bombs;
    PowerUpData activePower;
    int direction; // gora, dol , lewo, prawo
    int frame;
    ALLEGRO_COLOR color;
    int controlKeys[6];
} Player;

// FUKCJE
void initPlayer(Player* players, int playerIndex, unsigned int health, int x, int y, float velocity, int bombAmount, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);
void drawPlayer(Player* player,int playerNumber, ALLEGRO_BITMAP* gameDisplay);
void movePlayer(Player* player, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, struct Bomb* bomb);
void placeBomb(Player* players, int playerNumber, struct Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState);

#endif /* PLAYER_H */