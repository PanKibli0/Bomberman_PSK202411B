#ifndef MAP_H
#define MAP_H

#include "block.h"
#include "config.h"
#include "player.h"


void mapLayout(Block** blocks,Player* players, int playerNumber, int mapIndex, int *CHANCE);

#endif /* MAP_H */