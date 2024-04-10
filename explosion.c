#include "explosion.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// RYSOWANIE 




    // DZIALANIE
// EKSPPLOZJA - BLOKI
void explosionBlock(Bomb* bomb, Block** blocks) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

    bool destroyed = false; // flaga czy bylo zniszczenie

    // Środek
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

    // Dół
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

// EKSPLOZJA - GRACZ


void explosionPlayer(Bomb* bomb, Player* players, int playerNumber) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

    bool damaged = false;

    printf("%d %d\n", players[0].position.x, players[0].position.y);
    // Srodek
    
    for (int i = 0; i < playerNumber; i++) {
        if (!damaged && players[i].position.x >= x - 20 && players[i].position.x <= x + 20 &&
            players[i].position.y >= y - 20 && players[i].position.y <= y + 20) {
            printf("\tSRODEK\n");
            players[i].health -= 1;
            damaged = true;
            break;
        }
    }
    
    // Prawo
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (!damaged && players[j].position.y == y && players[j].position.x > x && players[j].position.x <= x + 40 * i + 60) {
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
            if (!damaged && players[j].position.y == y && players[j].position.x < x && players[j].position.x >= x - 40 * i - 60) {
                players[j].health -= 1;
                damaged = true;
                break;
            }
        }
    }

    // DOL
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (!damaged && players[j].position.x == x && players[j].position.y > y && players[j].position.y <= y + 40 * i + 60) {            
                players[j].health -= 1;
            damaged = true;
            break;
            }
        }
    }

    // GORA
    damaged = false;
    for (int i = 1; i <= power; i++) {
        for (int j = 0; j < playerNumber; j++) {
            if (!damaged && players[j].position.x == x && players[j].position.y < y && players[j].position.y >= y - 40 * i - 60) {
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
