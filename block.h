#ifndef BLOCK_H
#define BLOCK_H

#include <allegro5/allegro.h>
#include "position.h"

typedef struct Block {
    int health;
    Position position;
    ALLEGRO_BITMAP* graphic;
    struct Block* next;
} Block;

void addBlock(Block** block, int x, int y, int health);
void drawBlocks(Block* block, ALLEGRO_BITMAP* gameDisplay);

#endif /* BLOCK_H */