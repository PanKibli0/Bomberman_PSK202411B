/**
 * @file bomb.c
 * @brief Plik implementacji bomby i jej funkcjonalnoœci.
 */
#include <allegro5/allegro.h>

#include "config.h"
#include "bomb.h"
#include "explosion.h"
#include "player.h"
#include "graphics.h"
#include "sounds.h"

 /**
  * @brief Dodaje now¹ bombê do listy bomb.
  *
  * Funkcja sprawdza, czy na pozycji (x, y) nie jest ju¿ ustawiona bomba,
  * a nastêpnie tworzy now¹ bombê, ustawia jej pozycjê, moc, czas do wybuchu,
  * w³aœciciela oraz grafikê. Dodaje now¹ bombê na pocz¹tek listy bomb.
  *
  * @param bomb Podwójny wskaŸnik na pocz¹tek listy bomb na planszy.
  * @param x Pozycja x nowej bomby.
  * @param y Pozycja y nowej bomby.
  * @param power Moc wybuchu nowej bomby.
  * @param owner WskaŸnik na w³aœciciela nowej bomby.
  * @return true jeœli dodanie bomby powiod³o siê, false w przeciwnym wypadku.
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
 * @param bomb WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 */
void drawBombs(Bomb* bomb, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        al_draw_bitmap(bombElement->graphic, bombElement->position.x, bombElement->position.y, 0);
    }
}

/**
 * @brief Usuwa bombê z listy bomb i zwalnia zajêt¹ przez ni¹ pamiêæ.
 *
 * Funkcja usuwa wskazan¹ bombê z listy bomb, niszczy jej bitmapê
 * i zwalnia zajêt¹ przez ni¹ pamiêæ.
 *
 * @param bombs Podwójny wskaŸnik na pocz¹tek listy bomb na planszy.
 * @param explodedBomb WskaŸnik na bombê do usuniêcia.
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
 * @brief Aktualizuje stan bomb i sprawdza, czy któraœ z nich powinna wybuchn¹æ.
 *
 * Funkcja zmniejsza czas do wybuchu ka¿dej bomby, a jeœli czas bomby up³yn¹³,
 * powoduje jej wybuch, usuwaj¹c j¹ z listy bomb, niszcz¹c bloki, rani¹c graczy
 * oraz generuj¹c wybuch.
 *
 * @param bombs Podwójny wskaŸnik na pocz¹tek listy bomb na planszy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podwójny wskaŸnik na pocz¹tek listy wybuchów.
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
 * @brief Umieszcza bombê przez graczy.
 *
 * Funkcja sprawdza, czy gracz nacisn¹³ odpowiedni klawisz i czy mo¿e umieœciæ bombê,
 * a nastêpnie oblicza pozycjê bomby na podstawie pozycji gracza i dodaje j¹ do listy bomb.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param bomb Podwójny wskaŸnik na pocz¹tek listy bomb na planszy.
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