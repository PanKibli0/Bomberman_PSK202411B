#include "position.h"
#include "player.h"
#include "bomb.h"
#include "block.h"


bool checkBlockCollision(float x, float y, Block* block) {
    for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
        if (x + TILE > blockElement->position.x && x < blockElement->position.x + TILE &&
            y + TILE > blockElement->position.y && y < blockElement->position.y + TILE) {
            return true;
        }
    }
    return false;
}

bool checkBombCollision(float x, float y, Bomb* bomb) {
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        if (x + TILE > bombElement->position.x && x < bombElement->position.x + TILE &&
            y + TILE > bombElement->position.y && y < bombElement->position.y + TILE) {
            return true;
        }
    }
    return false;
}

bool checkPlayerCollision(float x, float y, Player* players, int playerNumber, int currentPlayerIndex) {
    for (int i = 0; i < playerNumber; ++i) {
        if (i != currentPlayerIndex) {
            if (players[i].health > 0) {
                if (x + TILE > players[i].position.x && x < players[i].position.x + TILE &&
                    y + TILE > players[i].position.y && y < players[i].position.y + TILE) {
                    return true;
                }
            }
        }
    }
    return false;
}