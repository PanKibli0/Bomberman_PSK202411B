#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bomb.h"
#include "block.h"


bool checkBlockCollision(float x, float y, int range, Block* block);
bool checkBombCollision(float x, float y, Bomb* bomb);
bool checkPlayerCollision(float x, float y, int range, Player* players, int playerNumber, int currentPlayerIndex);

#endif /* COLLISION_H */