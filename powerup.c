
#include "powerup.h"
#include "graphics.h"
#include "bomb.h"
#include "sounds.h"


void deactivatedOtherPowers(Player* player) {
    player->activePower.kick = false;
    player->activePower.bombThief.active = false;
    player->activePower.randomTeleport = false;
    player->activePower.bombThief.hold = false;
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
        if (players[i].health <= 0) continue;
        if (players[i].position.x - TILE / 2 <= x && players[i].position.x + TILE / 2 >= x &&
            players[i].position.y - TILE / 2 <= y && players[i].position.y + TILE / 2 >= y) {
            return false;
        }
    }

    return true;
}

void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs) {
    int x = rand() % 17 * TILE+TILE, y = rand() % 9 * TILE+TILE;
    if (!isPositionEmpty(x, y, players, playerNumber, blocks, bombs, *powerUps)) return;

    PowerUp* newPowerUp = malloc(sizeof(PowerUp));

    newPowerUp->type = rand() % TYPES_NUMBER;
    newPowerUp->position.x = x;
    newPowerUp->position.y = y;
    newPowerUp->lifeTime = 7.0;

    // Grafika dla power-upów
    newPowerUp->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newPowerUp->graphic);
    switch (newPowerUp->type) {
    case HEALTH:
        al_draw_scaled_bitmap(powerHealthGraphic, 0, 0, al_get_bitmap_width(powerHealthGraphic), al_get_bitmap_height(powerHealthGraphic), 0, 0, TILE, TILE, 0);
        break;
    case BOMB_POWER_UP:
        al_draw_scaled_bitmap(powerBombPowerUpGraphic, 0, 0, al_get_bitmap_width(powerBombPowerUpGraphic), al_get_bitmap_height(powerBombPowerUpGraphic), 0, 0, TILE, TILE, 0);
        break;
    case BOMB_POWER_DOWN:
        al_draw_scaled_bitmap(powerBombPowerDownGraphic, 0, 0, al_get_bitmap_width(powerBombPowerDownGraphic), al_get_bitmap_height(powerBombPowerDownGraphic), 0, 0, TILE, TILE, 0);
        break;
    case VELOCITY_UP:
        al_draw_scaled_bitmap(powerVelocityUpGraphic, 0, 0, al_get_bitmap_width(powerVelocityUpGraphic), al_get_bitmap_height(powerVelocityUpGraphic), 0, 0, TILE, TILE, 0);
        break;
    case VELOCITY_DOWN:
        al_draw_scaled_bitmap(powerVelocityDownGraphic, 0, 0, al_get_bitmap_width(powerVelocityDownGraphic), al_get_bitmap_height(powerVelocityDownGraphic), 0, 0, TILE, TILE, 0);
        break;
    case BOMB_LIMIT_UP:
        al_draw_scaled_bitmap(powerBombLimitUpGraphic, 0, 0, al_get_bitmap_width(powerBombLimitUpGraphic), al_get_bitmap_height(powerBombLimitUpGraphic), 0, 0, TILE, TILE, 0);
        break;
    case BOMB_LIMIT_DOWN:
        al_draw_scaled_bitmap(powerBombLimitDownGraphic, 0, 0, al_get_bitmap_width(powerBombLimitDownGraphic), al_get_bitmap_height(powerBombLimitDownGraphic), 0, 0, TILE, TILE, 0);
        break;
    case SHIELD:
        al_draw_scaled_bitmap(powerShieldGraphic, 0, 0, al_get_bitmap_width(powerShieldGraphic), al_get_bitmap_height(powerShieldGraphic), 0, 0, TILE, TILE, 0);
        break;
    case INVISIBILITY:
        al_draw_scaled_bitmap(powerInvisibilityGraphic, 0, 0, al_get_bitmap_width(powerInvisibilityGraphic), al_get_bitmap_height(powerInvisibilityGraphic), 0, 0, TILE, TILE, 0);
        break;
    case KICK:
        al_draw_scaled_bitmap(powerKickGraphic, 0, 0, al_get_bitmap_width(powerKickGraphic), al_get_bitmap_height(powerKickGraphic), 0, 0, TILE, TILE, 0);
        break;
    case BOMB_THIEF:
        al_draw_scaled_bitmap(powerBombThiefGraphic, 0, 0, al_get_bitmap_width(powerBombThiefGraphic), al_get_bitmap_height(powerBombThiefGraphic), 0, 0, TILE, TILE, 0);
        break;
    case RANDOM_TELEPORT:
        al_draw_scaled_bitmap(powerRandomTeleportGraphic, 0, 0, al_get_bitmap_width(powerRandomTeleportGraphic), al_get_bitmap_height(powerRandomTeleportGraphic), 0, 0, TILE, TILE, 0);
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
                
                al_play_sample(powerUpSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

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
                    players[i].velocity += 0.2;
                    break;
                case VELOCITY_DOWN:
                    if (players[i].velocity > 1) {
                        players[i].velocity -= 0.25;
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
                    players[i].activePower.invisibility = 3.0;
                    break;
                case KICK:
                    deactivatedOtherPowers(&players[i]);
                    players[i].activePower.kick = true;
                    break;
                case BOMB_THIEF:
                    deactivatedOtherPowers(&players[i]);
                    players[i].activePower.bombThief.active = true;
                    break;
                case RANDOM_TELEPORT:
                    deactivatedOtherPowers(&players[i]);
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
                if (players[i].activePower.kick) {
                    powerKick(&players[i], players, playerNumber, blocks, bombs);
                    break;
                }
                else if (players[i].activePower.bombThief.active) {
                    powerBombThief(&players[i], bombs);
                    break;
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

void powerKick(Player* player, Player* players, int playerNumber, Block* blocks, Bomb** bombs) {
    int x = player->position.x;
    int y = player->position.y;

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
        if (bombElement->position.x >= x - TILE / 3 && bombElement->position.x <= x + TILE / 3 &&
            bombElement->position.y >= y - TILE / 3 && bombElement->position.y <= y + TILE / 3) {

            int dx = x - player->position.x;
            int dy = y - player->position.y;
            int newX = bombElement->position.x, newY = bombElement->position.y;

            while (isPositionEmpty(newX + dx, newY + dy, players, playerNumber, blocks, *bombs, NULL)) {
                newX += dx;
                newY += dy;
            }

            bombElement->position.x = newX;
            bombElement->position.y = newY;
            
            return;
        }
    }
}


void powerBombThief(Player* player, Bomb** bombs) {
    int x = player->position.x;
    int y = player->position.y;

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
        if (bombElement->position.x >= x - TILE / 3 && bombElement->position.x <= x + TILE / 3 &&
            bombElement->position.y >= y - TILE / 3 && bombElement->position.y <= y + TILE / 3) {
            if (bombElement->owner != NULL) {
                bombElement->owner->bombs.bombAmount++;
            }
            explodedBomb(bombs, bombElement);
            player->activePower.bombThief.active = false;
            player->activePower.bombThief.hold = true;
            player->bombs.bombAmount++;
            return;
        }
    }
}



void powerTeleport(Player* player, Block* blocks, Bomb* bombs, PowerUp* powerUps) {
    int x, y;
    do {
        x = rand() % 17 * TILE+TILE;
        y = rand() % 9 * TILE+TILE;
    } while (!isPositionEmpty(x, y, player, 1, blocks, bombs, powerUps));

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