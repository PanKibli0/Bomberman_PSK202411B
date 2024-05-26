#include "config.h"
#include "player.h"
#include "bomb.h"
#include "block.h"



bool checkBlockCollision(float x, float y, Block* block) {
    for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
        if (x + TILE - 6 > blockElement->position.x &&
            x + 6 < blockElement->position.x + TILE &&
            y + TILE - 6 > blockElement->position.y &&
            y + 6 < blockElement->position.y + TILE) {
            return true;
        }
    }
    return false;
}

bool checkBombCollision(float x, float y, Bomb* bomb) {
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        if (x + TILE - 6 > bombElement->position.x &&
            x + 6 < bombElement->position.x + TILE &&
            y + TILE - 6 > bombElement->position.y &&
            y + 6 < bombElement->position.y + TILE) {
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