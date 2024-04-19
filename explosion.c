#include "explosion.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "bomb.h"

// RYSOWANIE 

void createExplosion(Explosion** explosions, int x, int y) {
    Explosion* newExplosion = malloc(sizeof(Explosion));

    newExplosion->position.x = x;
    newExplosion->position.y = y;
    newExplosion->direction = 1; // KODZIK ZMIANIA
    newExplosion->time = 0.2;

    newExplosion->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newExplosion->graphic);
    al_draw_filled_rectangle(0, 0, TILE, TILE, al_map_rgba(255, 0, 0, 50));


    newExplosion->next = *explosions;
    *explosions = newExplosion;
};


void drawExplosion(Explosion* explosions, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Explosion* explosion = explosions; explosion != NULL; explosion = explosion->next) {
        al_draw_bitmap(explosion->graphic, explosion->position.x, explosion->position.y, 0);
    }
}


void endExplosion(Explosion** explosions, Explosion* endExplosion) {
    if (*explosions == endExplosion) {
        *explosions = endExplosion->next;
    }
    else {
        for (Explosion* explosion = *explosions; explosion != NULL; explosion = explosion->next) {
            if (explosion->next == endExplosion) {
                explosion->next = endExplosion->next;
                break;
            }
        }
    }
    al_destroy_bitmap(endExplosion->graphic);
    free(endExplosion);
}

void endExplosions(Explosion** explosions) {
    for (Explosion* explosion = *explosions; explosion != NULL; explosion = explosion->next) {
        explosion->time -= 1.0 / FPS;

        if (explosion->time <= 0) {
            endExplosion(explosions, explosion);
            break;
        }
    }
}

// LOGIKA WYBUCHU
void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber, Explosion** explosions) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

    //printf("EXPLODE\n");
    createExplosion(explosions, x, y);


    bool destroyed = false; // Flaga oznaczająca, czy bomba zniszczyła blok
    bool damaged = false;   // Flaga oznaczająca, czy dany gracz został zraniony przez wybuch
    bool explode = false; // Flaga oznaczająca, czy nie ma bloku nie do zniszczniea

    // Środek
    for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
        if (blockElement->position.x == x && blockElement->position.y == y) {
            if (blockElement->health > 0) blockElement->health -= 1;
            if (blockElement->health == 0) breakBlock(blocks, blockElement);
            destroyed = true;
        }
    }

    if (!destroyed) {
        for (int i = 0; i < playerNumber; i++) {
            if (players[i].position.x == x  && players[i].position.y == y ) {
                if (!damaged) {
                    if (players[i].health > 0)
                        players[i].health -= 1;
                    damaged = true;
                }
            }
        }
    }

    // Prawo
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x + TILE * i;

        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == newX && blockElement->position.y == y) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }
        }

        if (!explode) createExplosion(explosions, newX, y);

        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.y == y && players[j].position.x > x && players[j].position.x <= newX + TILE) {
                    if (players[j].health > 0)
                        players[j].health -= 1;
                    damaged = true;
                    break;
                }
            }
        }
    }

    // Lewo
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x - TILE * i;

        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == newX && blockElement->position.y == y) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }

        }

        if (!explode) createExplosion(explosions, newX, y);

        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.y == y && players[j].position.x < x && players[j].position.x >= newX - TILE) {
                    if (players[j].health > 0)
                        players[j].health -= 1;
                    damaged = true;
                    break;
                }
            }
        }
    }

    // Góra
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y - TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == newY) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }
        }

        if (!explode) createExplosion(explosions, x, newY);

        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.x == x && players[j].position.y < y && players[j].position.y >= newY - TILE) {
                    if (players[j].health > 0)
                        players[j].health -= 1;
                    damaged = true;
                    break;
                }
            }
        }
    }

    // Dół
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y + TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == newY) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }
        }

        if (!explode) createExplosion(explosions, x, newY);


        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (!damaged && players[j].position.x == x && players[j].position.y > y && players[j].position.y <= newY+TILE) {
                    printf("PLAYER EXP\n");
                    if (players[j].health > 0)
                        players[j].health -= 1;
                    damaged = true;
                    break;
                }
            }
        }
    }

    printf("\tH0: %d\n", players[0].health);
    printf("\tH1: %d\n", players[1].health);
}
