#include <allegro5/allegro_primitives.h>
#include "powerup.h"
#include "graphics.h"
#include "bomb.h"
#include <stdio.h>

void deactivatedOtherPowers(Player* player) {
    player->activePower.kick = false;
    player->activePower.bombThief.active = false;
    player->activePower.randomTeleport = false;

}


bool isPositionEmpty(int x, int y, Player* players, int playerNumber, Block* blocks, Bomb* bombs, PowerUp* powerUps) {
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
        if (players[i].health >= 0) continue;
        if (players[i].position.x - TILE / 2 <= x && players[i].position.x + TILE / 2 >= x &&
            players[i].position.y - TILE / 2 <= y && players[i].position.y + TILE / 2 >= y) {
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
    newPowerUp->type = TYPES_NUMBER - 2;
    newPowerUp->position.x = x;
    newPowerUp->position.y = y;
    newPowerUp->lifeTime = 4.0;

    // Grafika dla power-upów
    newPowerUp->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newPowerUp->graphic);
    switch (newPowerUp->type) {
    case HEALTH:
        // Zielony kolor dla power-upu zwiêkszaj¹cego zdrowie
        al_clear_to_color(al_map_rgba(0, 255, 0, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case BOMB_POWER_UP:
        // Niebieski kolor dla power-upu zwiêkszaj¹cego moc bomb
        al_clear_to_color(al_map_rgba(0, 0, 255, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case BOMB_POWER_DOWN:
        // Czerwony kolor dla power-upu zmniejszaj¹cego moc bomb
        al_clear_to_color(al_map_rgba(255, 0, 0, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case VELOCITY_UP:
        // ¯ó³ty kolor dla power-upu zwiêkszaj¹cego prêdkoœæ
        al_clear_to_color(al_map_rgba(255, 255, 0, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case VELOCITY_DOWN:
        // Pomarañczowy kolor dla power-upu zmniejszaj¹cego prêdkoœæ
        al_clear_to_color(al_map_rgba(255, 165, 0, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case BOMB_LIMIT_UP:
        // Fioletowy kolor dla power-upu zwiêkszaj¹cego limit bomb
        al_clear_to_color(al_map_rgba(128, 0, 128, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case BOMB_LIMIT_DOWN:
        // Ró¿owy kolor dla power-upu zmniejszaj¹cego limit bomb
        al_clear_to_color(al_map_rgba(255, 20, 147, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case SHIELD:
        // Szary kolor dla power-upu daj¹cego tarczê
        al_clear_to_color(al_map_rgba(128, 128, 128, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case INVISIBILITY:
        // Ciemnoniebieski kolor dla power-upu niewidzialnoœci
        al_clear_to_color(al_map_rgba(0, 0, 128, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case KICK:
        // Bia³y kolor dla power-upu daj¹cego mo¿liwoœæ kopania bomb
        al_clear_to_color(al_map_rgba(255, 255, 255, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case BOMB_THIEF:
        // Zielony kolor dla power-upu kradn¹cego bomby
        al_clear_to_color(al_map_rgba(0, 128, 0, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    case RANDOM_TELEPORT:
        // Br¹zowy kolor dla power-upu losowej zmiany pozycji
        al_clear_to_color(al_map_rgba(165, 42, 42, 20));
        al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(0, 0, 0), 5);
        break;
    }


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
                case SHIELD:
                    players[i].activePower.shieldTime += 3.0;
                    break;
                case INVISIBILITY:
                    players[i].activePower.invisibility = 8.0; 
                    break;
                case KICK:
                    deactivatedOtherPowers(&players[i]);
                    players[i].activePower.kick = true;
                    break;
                case BOMB_THIEF:
                    players[i].activePower.bombThief.active = true;
                    break;
                case RANDOM_TELEPORT:
                    players[i].activePower.randomTeleport = true;
                    break;
            }
                destroyPowerUp(powerUps, powerUp);
                break;
            }
        }
    }
}

void disappearancePowerUp(PowerUp** powerUps) {
    for (PowerUp* powerUpElement = *powerUps; powerUpElement != NULL; powerUpElement = powerUpElement->next) {
        powerUpElement->lifeTime -= 1.0 / FPS;

        if (powerUpElement->lifeTime <= 0) {
            destroyPowerUp(powerUps, powerUpElement);
            break;
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


// DZIALANIE POSZCZEGOLNYCH POWERUP

void usePower(Player* players, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* blocks, Bomb** bombs, PowerUp* powerUps) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].health > 0) {
            if (al_key_down(keyState, players[i].controlKeys[5])) {
                printf("\nPOWER USED");
                if (players[i].activePower.kick) {
                    // powerKick(players[i].position.x, players[i].position.y, players[i].direction, blocks, bombs);
                    break;
                }
                else if (players[i].activePower.bombThief.active) {
                    powerBombThief(&players[i], &bombs);
                }
                else if (players[i].activePower.randomTeleport) {
                    powerTeleport(&players[i], blocks, *bombs, powerUps);
                    players[i].activePower.randomTeleport = false;
                    break;
                }
            }
        }
    }
}

void powerBombThief(Player* player, Bomb** bombs) {
    int x = player->position.x / TILE * TILE;
    int y = player->position.y / TILE * TILE;

    switch (player->direction) {
    case 1:
        y -= TILE;
        break;
    case 2:
        y += TILE;
        break;
    case 3:
        x += TILE;
        break;
    case 4:
        x -= TILE;
        break;
    }
    
    for (Bomb* bombElement = *bombs; bombElement != NULL; bombElement = bombElement->next) {
        if (bombElement->position.x == x && bombElement->position.y == y) {
            explodedBomb(bombs, bombElement);          
            return;
        }
        
    }
}


void powerTeleport(Player* player, Block* blocks, Bomb* bombs, PowerUp* powerUps) {
    int x, y;
    do {
        x = rand() % (XNUMBER - 2) * TILE;
        y = rand() % (YNUMBER - 2) * TILE;
    } while (!isPositionEmpty(x, y, player, 1, blocks, bombs, powerUps) );
 
    player->position.x = x;
    player->position.y = y;
}


void powerShield(Player* players, int playerNumber) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].activePower.shieldTime > 0)
            players[i].activePower.shieldTime -= 1.0 / FPS;

    };
}

void powerInvisibility(Player* players, int playerNumber) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].activePower.invisibility > 0)
            players[i].activePower.invisibility -= 1.0 / FPS;
    };
}