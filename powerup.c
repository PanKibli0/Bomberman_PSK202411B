#include <allegro5/allegro_primitives.h>
#include "powerup.h"
#include "graphics.h"

bool isPositionEmpty(int x, int y, Player* players, int playerNumber, Block* blocks, Bomb* bombs, PowerUp* powerUps) {
    // Sprawdzanie czy pozycja jest pusta (nie ma bloków, gracza, innych power-upów ani bomb)
    for (Block* block = blocks; block != NULL; block = block->next) {
        if (block->position.x == x && block->position.y == y) {
            return false;
        }
    }

    for (PowerUp* powerUp = powerUps; powerUp != NULL; powerUp = powerUp->next) {
        if (powerUp->position.x == x && powerUp->position.y == y) {
            return false;
        }
    }

    for (Bomb* bomb = bombs; bomb != NULL; bomb = bomb->next) {
        if (bomb->position.x == x && bomb->position.y == y) {
            return false;
        }
    }

    for (int i = 0; i < playerNumber; i++) {
        if (players[i].health == 0) continue;
        if (players[i].position.x == x && players[i].position.y == y) {
            return false;
        }
    }

    return true;
}

void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs) {
    int x = rand() % (XNUMBER - 2) * TILE, y = rand() % (YNUMBER - 2) * TILE;
    if (!isPositionEmpty(x, y, players, playerNumber, blocks, bombs, *powerUps)) return;

    PowerUp* newPowerUp = malloc(sizeof(PowerUp));

    newPowerUp->type = rand() % TYPES_NUMBER-1;
    newPowerUp->position.x = x;
    newPowerUp->position.y = y;

    // Grafika dla power-upów
    newPowerUp->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newPowerUp->graphic);
    al_clear_to_color(al_map_rgba(rand()%255, rand() % 255, rand() % 255, 20)); 
    al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5); 

    newPowerUp->next = *powerUps;
    *powerUps = newPowerUp;
}

void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay) { 
    al_set_target_bitmap(gameDisplay);
    for (PowerUp* powerUp = powerUps; powerUp != NULL; powerUp = powerUp->next) {
        al_draw_bitmap(powerUp->graphic, powerUp->position.x, powerUp->position.y, 0);
        
    }
}

void collectPowerUp(Player* players, int playerNumber, PowerUp** powerUps) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].health == 0) continue;
        for (PowerUp* powerUp = *powerUps; powerUp != NULL; powerUp = powerUp->next) {
            if (players[i].position.x < powerUp->position.x + TILE / 2 &&
                players[i].position.x + TILE > powerUp->position.x &&
                players[i].position.y < powerUp->position.y + TILE / 2 &&
                players[i].position.y + TILE > powerUp->position.y) {
                // Kolekcja power-upu
                switch (powerUp->type) {
                case HEALTH:
                    players[i].health++;
                    break;
                case BOMB_POWER_UP:
                    players[i].bombs.BombPower += 1;
                    break;
                case BOMB_POWER_DOWN:
                    if (players[i].bombs.BombPower > 1) {
                        players[i].bombs.BombPower -= 1;
                    }
                    break;
                case VELOCITY_UP:
                    players[i].velocity += 1;
                    break;
                case VELOCITY_DOWN:
                    if (players[i].velocity > 1) {
                        players[i].velocity -= 1;
                    }
                    break;
                case BOMB_LIMIT_UP:
                    players[i].bombs.bombAmount += 1;
                    break;
                case BOMB_LIMIT_DOWN:
                    if (players[i].bombs.bombAmount > 1) {
                        players[i].bombs.bombAmount -= 1;
                    }
                }
                destroyPowerUp(powerUps, powerUp);
                break;
            }
        }
    }
}

void destroyPowerUp(PowerUp** powerUps, PowerUp* powerUp) {
    if (*powerUps == powerUp) {
        *powerUps = powerUp->next;
    }
    else {
        for (PowerUp* powerUpElement = *powerUps; powerUpElement != NULL; powerUpElement = powerUpElement->next) {
            if (powerUpElement->next == powerUp) {
                powerUpElement->next = powerUp->next;
                break;
            }
        }
    }
    al_destroy_bitmap(powerUp->graphic);
    free(powerUp);
}
