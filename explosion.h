#ifndef EXPLOSION_H
#define EXPLOSION_H
/**
 * @file explosion.h
 * @brief Plik implementacji struktury bomby i funckji wybuchu bomby.
 */
#include "config.h"
#include "player.h"
#include "block.h"

 /**
  * @brief Struktura reprezentuj�ca wybuch.
  *
  * Struktura zawiera informacje o pozycji wybuchu, czasie trwania oraz grafice.
  */
typedef struct Explosion {
    Position position;          /**< Pozycja wybuchu */
    float time;                 /**< Czas trwania wybuchu */
    ALLEGRO_BITMAP* graphic;    /**< Grafika wybuchu */
    struct Explosion* next;     /**< Wska�nik na nast�pny wybuch w li�cie */
} Explosion;

// FUNKCJE

/**
 * @brief Wywo�uje wybuch bomby.
 *
 * Funkcja generuje wybuch na podstawie podanej bomby, niszcz�c bloki, rani�c graczy
 * oraz tworz�c nowe wybuchy na podstawie mocy bomby.
 *
 * @param bomb Wska�nik na bomb�, kt�ra wybuch�a.
 * @param blocks Podw�jny wska�nik na pocz�tek listy blok�w na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podw�jny wska�nik na pocz�tek listy wybuch�w.
 */
void explosion(struct Bomb* bomb, Block** blocks, Player* players, int playerNumber, Explosion** explosions);

/**
 * @brief Rysuje wszystkie wybuchy na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekran gry i rysuje wszystkie wybuchy
 * z listy wybuch�w w odpowiednich pozycjach.
 *
 * @param explosions Podw�jny wska�nik na pocz�tek listy wybuch�w.
 * @param gameDisplay Bitmapa reprezentuj�ca ekran gry.
 */
void drawExplosion(Explosion** explosions, ALLEGRO_BITMAP* gameDisplay);

/**
 * @brief Zwalnia pami�� zaj�t� przez wybuchy.
 *
 * Funkcja usuwa wszystkie wybuchy z listy wybuch�w i zwalnia zaj�t� przez nie pami��.
 *
 * @param explosions Podw�jny wska�nik na pocz�tek listy wybuch�w.
 */
void endExplosions(Explosion** explosions);

#endif /* EXPLOSION_H */