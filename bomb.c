/**
 * @file bomb.c
 * @brief Plik implementacji bomby i jej funkcjonalno�ci.
 */
#include <allegro5/allegro.h>

#include "config.h"
#include "bomb.h"
#include "explosion.h"
#include "player.h"
#include "graphics.h"
#include "sounds.h"

 /**
  * @brief Dodaje now� bomb� do listy bomb.
  *
  * Funkcja sprawdza, czy na pozycji (x, y) nie jest ju� ustawiona bomba,
  * a nast�pnie tworzy now� bomb�, ustawia jej pozycj�, moc, czas do wybuchu,
  * w�a�ciciela oraz grafik�. Dodaje now� bomb� na pocz�tek listy bomb.
  *
  * @param bomb Podw�jny wska�nik na pocz�tek listy bomb na planszy.
  * @param x Pozycja x nowej bomby.
  * @param y Pozycja y nowej bomby.
  * @param power Moc wybuchu nowej bomby.
  * @param owner Wska�nik na w�a�ciciela nowej bomby.
  * @return true je�li dodanie bomby powiod�o si�, false w przeciwnym wypadku.
  */
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

/**
 * @brief Ustawia bomby na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekranie i ustawia wszystkie bomby
 * z listy bomb w odpowiednich pozycjach.
 *
 * @param bomb Wska�nik na pocz�tek listy bomb na planszy.
 * @param gameDisplay Bitmapa reprezentuj�ca ekran gry.
 */
void drawBombs(Bomb* bomb, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        al_draw_bitmap(bombElement->graphic, bombElement->position.x, bombElement->position.y, 0);
    }
}

/**
 * @brief Usuwa bomb� z listy bomb i zwalnia zaj�t� przez ni� pami��.
 *
 * Funkcja usuwa wskazan� bomb� z listy bomb, niszczy jej bitmap�
 * i zwalnia zaj�t� przez ni� pami��.
 *
 * @param bombs Podw�jny wska�nik na pocz�tek listy bomb na planszy.
 * @param explodedBomb Wska�nik na bomb� do usuni�cia.
 */
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

/**
 * @brief Aktualizuje stan bomb i sprawdza, czy kt�ra� z nich powinna wybuchn��.
 *
 * Funkcja zmniejsza czas do wybuchu ka�dej bomby, a je�li czas bomby up�yn��,
 * powoduje jej wybuch, usuwaj�c j� z listy bomb, niszcz�c bloki, rani�c graczy
 * oraz generuj�c wybuch.
 *
 * @param bombs Podw�jny wska�nik na pocz�tek listy bomb na planszy.
 * @param blocks Wska�nik na pocz�tek listy blok�w na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podw�jny wska�nik na pocz�tek listy wybuch�w.
 */
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

/**
 * @brief Umieszcza bomb� przez graczy.
 *
 * Funkcja sprawdza, czy gracz nacisn�� odpowiedni klawisz i czy mo�e umie�ci� bomb�,
 * a nast�pnie oblicza pozycj� bomby na podstawie pozycji gracza i dodaje j� do listy bomb.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param bomb Podw�jny wska�nik na pocz�tek listy bomb na planszy.
 * @param keyState Stan klawiatury.
 */
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