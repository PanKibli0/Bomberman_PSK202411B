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
    newExplosion->time = 0.6;

    newExplosion->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newExplosion->graphic);
    al_draw_filled_rectangle(0, 0, TILE, TILE, al_map_rgba(255, 0, 0, 50));

    
    newExplosion->next = *explosions;
    *explosions = newExplosion;
};


void drawExplosion(Explosion* explosions, ALLEGRO_DISPLAY* display) {
    for (Explosion* explosion = explosions; explosion != NULL; explosion = explosion->next) { 
        al_set_target_bitmap(al_get_backbuffer(display));
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

    printf("EXPLODE\n");
    createExplosion(explosions, x, y);
    

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
            if (players[i].position.x >= x - TILE/3 && players[i].position.x <= x + TILE/3 &&
                players[i].position.y >= y - TILE/3 && players[i].position.y <= y + TILE/3) {
                printf("\tSRODEK\n");
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

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x + TILE * i;
        createExplosion(explosions, newX, y);
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
                    if (players[i].health > 0)
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

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x - TILE * i;
        createExplosion(explosions, newX, y);
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
                    if (players[i].health > 0)
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

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y - TILE * i;
        createExplosion(explosions, x, newY);
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
                    if (players[i].health > 0)
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

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y + TILE * i;
        createExplosion(explosions, x, newY);
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
                    if (players[i].health > 0)
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

