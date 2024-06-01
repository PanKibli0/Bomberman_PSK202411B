#include <allegro5/allegro.h>


#include "config.h"
#include "bomb.h"
#include "explosion.h"
#include "player.h"
#include "graphics.h"
#include "sounds.h"


bool addBomb(Bomb** bomb, int x, int y, int power, Player* owner) {
    for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
        int dx = abs(bombElement->position.x - x);
        int dy = abs(bombElement->position.y - y);
        if (dx < TILE && dy < TILE) {
            return false;
        }
    }

    Bomb* newBomb = malloc(sizeof(Bomb));

    newBomb->position.x = x;
    newBomb->position.y = y;
    newBomb->power = power;
    newBomb->time = 3.0;
    newBomb->owner = owner;

    newBomb->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newBomb->graphic);
    al_draw_scaled_bitmap(bombGraphic, 0, 0, al_get_bitmap_width(bombGraphic), al_get_bitmap_height(bombGraphic), 0, 0, TILE, TILE, 0);


    newBomb->next = *bomb;
    *bomb = newBomb;

    return true;
}


void drawBombs(Bomb* bomb, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        al_draw_bitmap(bombElement->graphic, bombElement->position.x, bombElement->position.y, 0);
    }
}

void explodedBomb(Bomb** bombs, Bomb* explodedBomb) {
    if (*bombs == explodedBomb) {
        *bombs = explodedBomb->next;
    }
    else {
        for (Bomb* bombElement = *bombs; bombElement != NULL; bombElement = bombElement->next) {
            if (bombElement->next == explodedBomb) {
                bombElement->next = explodedBomb->next;
                break;
            }
        }
    }
    al_destroy_bitmap(explodedBomb->graphic);
    free(explodedBomb);
}

void timerBomb(Bomb** bombs, Block* blocks, Player* players, int playerNumber, Explosion** explosions) {
    for (Bomb* bombElement = *bombs; bombElement != NULL; bombElement = bombElement->next) {
        bombElement->time -= 1.0 / FPS;

        if (bombElement->time <= 0) {          
            explosion(bombElement, &blocks, players, playerNumber, explosions);
            if (bombElement->owner != NULL) bombElement->owner->bombs.bombAmount++;
            explodedBomb(bombs, bombElement);
            al_play_sample(explosionSound, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            break;
        }
    }
}

void placeBomb(Player* players, int playerNumber, Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState) {
    for (int i = 0; i < playerNumber; i++) {
        if (al_key_down(keyState, players[i].controlKeys[4]) && players[i].bombs.bombAmount > 0 && players[i].health > 0) {
            bool onBomb = checkBombCollision(players[i].position.x, players[i].position.y, *bomb);
            if (!onBomb) {
                // Obliczanie pozycji bomby na podstawie pozycji gracza
                int bombX = ((int)(players[i].position.x + TILE / 2) / TILE) * TILE;
                int bombY = ((int)(players[i].position.y + TILE / 2) / TILE) * TILE;
                if (players[i].activePower.bombThief.hold) {
                    if (addBomb(bomb, bombX, bombY, players[i].bombs.BombPower, NULL)) {
                        players[i].bombs.bombAmount -= 1;
                        players[i].activePower.bombThief.hold = false;
                        players[i].activePower.bombThief.active = true;
                    }
                }
                else if (addBomb(bomb, bombX, bombY, players[i].bombs.BombPower, &players[i])) {
                    players[i].bombs.bombAmount -= 1;
                }
            }
        }
    }
}