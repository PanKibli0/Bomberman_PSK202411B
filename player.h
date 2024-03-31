#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
    

typedef struct {
    Position position;
    ALLEGRO_BITMAP* playerGraphic;
    int velocity;
    int bomb;
    ALLEGRO_COLOR color;
    int controlKeys[5];
} Player;

// FUKCJE
void initPlayer(Player* player, ALLEGRO_BITMAP* playerGraphic, int x, int y, int velocity, int bomb, ALLEGRO_COLOR color, int controlKeys[5]);
void drawPlayer(Player* player);
void movePlayer(Player* player, ALLEGRO_KEYBOARD_STATE* keyState);



#endif /* PLAYER_H */