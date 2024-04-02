
#include <math.h>
#include "position.h"
#include "player.h"
#include "bomb.h"
#include "block.h"

bool checkBlockCollision(float x, float y, Block* block) {

    for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
        if (x + 40 > blockElement->position.x && x < blockElement->position.x + 40 &&
            y + 40 > blockElement->position.y && y < blockElement->position.y + 40) {
            return true;
        }
    }

    return false;
}

bool checkBombCollision(float x, float y, Bomb* bomb) {
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        if (x+40 > bombElement->position.x && x < bombElement->position.x + 40 &&
            y+40 > bombElement->position.y && y < bombElement->position.y + 40) {
            return true;
        }
    }
    return false;
}

bool checkPlayerCollision(float x, float y, Player* players, int playerNumber, int currentPlayerIndex) {
    for (int i = 0; i < playerNumber; ++i) {
        if (i != currentPlayerIndex) {
            if (x + 40 > players[i].position.x && x < players[i].position.x + 40 &&
                y + 40 > players[i].position.y && y < players[i].position.y + 40) {
                return true;
            }
        }
    }
    return false;
}