#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bomb.h"
#include "block.h"


bool checkBlockCollision(float x, float y, Block* block);
bool checkBombCollision(float x, float y, Bomb* bomb);
bool checkPlayerCollision(float x, float y, Player* players, int playerNumber, int currentPlayerIndex);

#endif /* COLLISION_H */