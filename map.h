#ifndef MAP_H
#define MAP_H

#include "block.h"
#include "position.h"
#include "player.h"


void mapLayout(Block** blocks,Player* players, int playerNumber, int mapIndex);

#endif /* MAP_H */