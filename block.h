#ifndef BLOCK_H
#define BLOCK_H

#include "position.h"

typedef struct Block {
    int health;
    Position position;
    ALLEGRO_BITMAP* graphic;
    struct Block* next;
} Block;

void addBlock(Block** block, int x, int y, int health);
void drawBlocks(Block* block, ALLEGRO_DISPLAY* display);

#endif /* BLOCK_H */