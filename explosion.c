#include "explosion.h"

void explosion(Bomb* bomb, Block** blocks) {
    int x = bomb->position.x;
    int y = bomb->position.y;

    // PRAWO
    for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
        if (blockElement->position.x == x + 40 && blockElement->position.y == y) {
            breakBlock(blocks, blockElement);
            break;
        }
    }

    // LEWO
    for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
        if (blockElement->position.x == x - 40 && blockElement->position.y == y) {
            breakBlock(blocks, blockElement);
            break;
        }
    }

    // GORA
    for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
        if (blockElement->position.x == x && blockElement->position.y == y + 40 ) {
            breakBlock(blocks, blockElement);
            break;
        }
    }
    // DOL
    for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
        if (blockElement->position.x == x  && blockElement->position.y == y - 40) {
            breakBlock(blocks, blockElement);
            break;
        }
    }
}