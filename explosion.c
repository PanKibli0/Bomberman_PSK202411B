#include "explosion.h"

void explosionBlock(Bomb* bomb, Block** blocks) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

    ALLEGRO_BITMAP* explodeCenter = al_create_bitmap(40, 40);
    ALLEGRO_BITMAP* explodeBeam = al_create_bitmap(40, 40);

    bool destroyed = false;

    // Œrodek
    for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
        if (blockElement->position.x == x && blockElement->position.y == y) {
            blockElement->health -= 1;
            if (blockElement->health == 0) {
                breakBlock(blocks, blockElement);
            }
            destroyed = true;

        }
    }

    destroyed = false;
    // Prawo
    for (int i = 1; i <= power && !destroyed; i++) {
        for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
            if (blockElement->position.x == x + 40 * i && blockElement->position.y == y) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
                break;
            }
        }
    }

    // Lewo
    destroyed = false;
    for (int i = 1; i <= power && !destroyed; i++) {
        for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
            if (blockElement->position.x == x - 40 * i && blockElement->position.y == y) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
                break;
            }
        }
    }

    // Góra
    destroyed = false;
    for (int i = 1; i <= power && !destroyed; i++) {
        for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == y + 40 * i) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
                break;
            }
        }
    }

    // Dó³
    destroyed = false;
    for (int i = 1; i <= power && !destroyed; i++) {
        for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == y - 40 * i) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
                break;
            }
        }
    }
};


void explosionPlayer(Bomb* bomb, Player* players, int playerNumber) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

    bool damaged = false;

    // Œrodek
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].position.x == x && players[i].position.y == y) {
            players[i].health -= 1;
        }
    }

    // Prawo
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (players[j].position.x == x + 40 * i && players[j].position.y == y) {
                players[j].health -= 1;
                damaged = true;
                break;
            }
        }
    }

    // Lewo
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (players[j].position.x == x - 40 * i && players[j].position.y == y) {
                players[j].health -= 1;
                damaged = true;
                break;
            }
        }
    }

    // Góra
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (players[j].position.x == x && players[j].position.y == y + 40 * i) {
                players[j].health -= 1;
                damaged = true;
                break;
            }
        }
    }

    // Dó³
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (players[j].position.x == x && players[j].position.y == y - 40 * i) {
                players[j].health -= 1;
                damaged = true;
                break;
            }
        }
    }
}


void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber) {
    explosionBlock(bomb, blocks);
    explosionPlayer(bomb, players, playerNumber);
}