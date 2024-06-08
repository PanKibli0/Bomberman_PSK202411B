/**
 * @file powerup.c
 * @brief Plik implementacji powerupów i ich funkcji.
 */
#include "powerup.h"
#include "graphics.h"
#include "bomb.h"
#include "sounds.h"

#include <stdio.h>

/**
 * @brief Funkcja deaktywuj¹ca inne aktywne moce gracza.
 *
 * @param player WskaŸnik na strukturê gracza.
 */
void deactivatedOtherPowers(Player* player) {
    player->activePower.kick = false;
    player->activePower.bombThief.active = false;
    player->activePower.randomTeleport = false;
    player->activePower.bombThief.hold = false;
}

/**
 * @brief Sprawdza, czy dana pozycja na planszy jest pusta.
 *
 * @param x Wspó³rzêdna x pozycji.
 * @param y Wspó³rzêdna y pozycji.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'ów na planszy.
 * @return true Jeœli pozycja jest pusta.
 * @return false Jeœli pozycja nie jest pusta.
 */
bool isPositionEmpty(int x, int y, Player* players, int playerNumber, Block* blocks, Bomb* bombs, PowerUp* powerUps) {
    // Sprawdzenie kolizji z blokami
    for (Block* block = blocks; block != NULL; block = block->next) {
        if (block->position.x == x && block->position.y == y) {
            return false;
        }
    }

    // Sprawdzenie kolizji z PowerUp'ami
    for (PowerUp* powerUp = powerUps; powerUp != NULL; powerUp = powerUp->next) {
        if (powerUp->position.x == x && powerUp->position.y == y) {
            return false;
        }
    }

    // Sprawdzenie kolizji z bombami
    for (Bomb* bomb = bombs; bomb != NULL; bomb = bomb->next) {
        if (bomb->position.x == x && bomb->position.y == y) {
            return false;
        }
    }

    // Sprawdzenie kolizji z graczami
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].health <= 0) continue;
        if (players[i].position.x - TILE / 2 - 5 <= x &&
            players[i].position.x + TILE / 2 + 5 >= x &&
            players[i].position.y - TILE / 2 - 5 <= y &&
            players[i].position.y + TILE / 2 + 5 >= y) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Tworzy nowy PowerUp na planszy.
 *
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 */
void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs) {
    int x = rand() % 17 * TILE + TILE, y = rand() % 9 * TILE + TILE;
    if (!isPositionEmpty(x, y, players, playerNumber, blocks, bombs, *powerUps)) return;

    PowerUp* newPowerUp = malloc(sizeof(PowerUp));

    newPowerUp->type = rand() % TYPES_NUMBER;

    newPowerUp->position.x = x;
    newPowerUp->position.y = y;
    newPowerUp->lifeTime = 7.0;

    // Grafika dla PowerUp'ów
    newPowerUp->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newPowerUp->graphic);
    switch (newPowerUp->type) {
        // Rysowanie odpowiedniej grafiki dla danego typu PowerUp'a
    }

    newPowerUp->next = *powerUps;
    *powerUps = newPowerUp;
}

/**
 * @brief Rysuje PowerUp'y na ekranie gry.
 *
 * @param powerUps Lista PowerUp'ów do narysowania.
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 */
void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (PowerUp* powerUp = powerUps; powerUp != NULL; powerUp = powerUp->next) {
        al_draw_bitmap(powerUp->graphic, powerUp->position.x, powerUp->position.y, 0);
    }
}

/**
 * @brief Sprawdza, czy gracz zbiera PowerUp'a.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 */
void collectPowerUp(Player* players, int playerNumber, PowerUp** powerUps) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].health == 0) continue;
        for (PowerUp* powerUp = *powerUps; powerUp != NULL; powerUp = powerUp->next) {
            if (players[i].position.x - TILE / 2 <= powerUp->position.x &&
                players[i].position.x + TILE / 2 >= powerUp->position.x &&
                players[i].position.y - TILE / 2 <= powerUp->position.y &&
                players[i].position.y + TILE / 2 >= powerUp->position.y) {
                
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
                    players[i].velocity += 0.4;
                    break;
                case VELOCITY_DOWN:
                    if (players[i].velocity > 1) {
                        players[i].velocity -= 0.30;
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
/**
 * @brief Aktualizuje czas ¿ycia PowerUp'ów.
 *
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 */
void disappearancePowerUp(PowerUp** powerUps) {
    for (PowerUp* powerUpElement = *powerUps; powerUpElement != NULL; powerUpElement = powerUpElement->next) {
        powerUpElement->lifeTime -= 1.0 / FPS;

        if (powerUpElement->lifeTime <= 0) {
            destroyPowerUp(powerUps, powerUpElement);
            break;
        }
    }
}
/**
 * @brief Usuwa PowerUp z listy.
 *
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 * @param powerUp WskaŸnik na PowerUp do usuniêcia.
 */
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
/**
 * @brief Obs³uguje akcjê u¿ycia PowerUp'a przez gracza.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param keyState Stan klawiatury.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'ów na planszy.
 */
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
/**
 * @brief Akcja PowerUp'a "Kopniêcie".
 *
 * @param player WskaŸnik na gracza.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 */
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

            while (isPositionEmpty(newX + dx, newY + dy, players, playerNumber, blocks, *bombs, NULL, false)) {
                newX += dx;
                newY += dy;
            }

            bombElement->position.x = newX;
            bombElement->position.y = newY;
            
            return;
        }
    }
}

/**
 * @brief Akcja PowerUp'a "Z³odziej bomb".
 *
 * @param player WskaŸnik na gracza.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 */
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


/**
 * @brief Akcja PowerUp'a "Losowe teleportacje".
 *
 * @param player WskaŸnik na gracza.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'ów na planszy.
 */
void powerTeleport(Player* player, Block* blocks, Bomb* bombs, PowerUp* powerUps) {
    int x, y;
    do {
        x = rand() % 17 * TILE+TILE;
        y = rand() % 9 * TILE+TILE;
    } while (!isPositionEmpty(x, y, player, 1, blocks, bombs, powerUps));

    player->position.x = x;
    player->position.y = y;
}


/**
 * @brief Akcja PowerUp'a "Tarcza".
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 */
void powerShield(Player* players, int playerNumber) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].activePower.shieldTime > 0)
            players[i].activePower.shieldTime -= 1.0 / FPS;

    };
}
/**
 * @brief Akcja PowerUp'a "Niewidzialnoœæ".
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 */
void powerInvisibility(Player* players, int playerNumber) {
    for (int i = 0; i < playerNumber; i++) {
        if (players[i].activePower.invisibility > 0)
            players[i].activePower.invisibility -= 1.0 / FPS;
    };
}