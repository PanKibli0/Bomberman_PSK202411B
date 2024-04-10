#include "explosion.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// RYSOWANIE 




void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

    bool destroyed = false; // Flaga oznaczająca, czy bomba zniszczyła blok
    bool damaged = false;   // Flaga oznaczająca, czy dany gracz został zraniony przez wybuch

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

    if (!destroyed) {
        for (int i = 0; i < playerNumber; i++) {
            if (players[i].position.x >= x - TILE/2 && players[i].position.x <= x + TILE/2 &&
                players[i].position.y >= y - TILE/2 && players[i].position.y <= y + TILE/2) {
                printf("\tSRODEK\n");
                if (!damaged) { 
                    players[i].health -= 1;
                    damaged = true; 
                }
            }
        }
    }

    // Prawo
    destroyed = false;
    damaged = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x + TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == newX && blockElement->position.y == y) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
            }
        }
        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.y == y && players[j].position.x > x && players[j].position.x <= newX + TILE+TILE/2) {
                    players[j].health--;
                    damaged = true;
                    break;
                }
            }
        }
    }

    // Lewo
    destroyed = false;
    damaged = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x - TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == newX && blockElement->position.y == y) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
            }
        }
        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.y == y && players[j].position.x < x && players[j].position.x >= newX - TILE+TILE/2) {
                    players[j].health--;
                    damaged = true;
                    break;
                }
            }
        }
    }

    // Góra
    destroyed = false;
    damaged = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y - TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == newY) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
            }
        }
        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.x == x && players[j].position.y < y && players[j].position.y >= newY - TILE+TILE/2) {
                    players[j].health--;
                    damaged = true;
                    break;
                }
            }
        }
    }

    // Dół
    destroyed = false;
    damaged = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y + TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == newY) {
                blockElement->health -= 1;
                if (blockElement->health == 0) {
                    breakBlock(blocks, blockElement);
                }
                destroyed = true;
            }
        }
        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.x == x && players[j].position.y > y && players[j].position.y <= newY + TILE+TILE/2) {
                    players[j].health--;
                    damaged = true;
                    break;
                }
            }
        }
    }

    printf("\tH0: %d\n", players[0].health);
    printf("\tH1: %d\n", players[1].health);
}