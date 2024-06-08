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
  * @brief Struktura reprezentuj¹ca wybuch.
  *
  * Struktura zawiera informacje o pozycji wybuchu, czasie trwania oraz grafice.
  */
typedef struct Explosion {
    Position position;          /**< Pozycja wybuchu */
    float time;                 /**< Czas trwania wybuchu */
    ALLEGRO_BITMAP* graphic;    /**< Grafika wybuchu */
    struct Explosion* next;     /**< WskaŸnik na nastêpny wybuch w liœcie */
} Explosion;

// FUNKCJE

/**
 * @brief Wywo³uje wybuch bomby.
 *
 * Funkcja generuje wybuch na podstawie podanej bomby, niszcz¹c bloki, rani¹c graczy
 * oraz tworz¹c nowe wybuchy na podstawie mocy bomby.
 *
 * @param bomb WskaŸnik na bombê, która wybuch³a.
 * @param blocks Podwójny wskaŸnik na pocz¹tek listy bloków na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podwójny wskaŸnik na pocz¹tek listy wybuchów.
 */
void explosion(struct Bomb* bomb, Block** blocks, Player* players, int playerNumber, Explosion** explosions);

/**
 * @brief Rysuje wszystkie wybuchy na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekran gry i rysuje wszystkie wybuchy
 * z listy wybuchów w odpowiednich pozycjach.
 *
 * @param explosions Podwójny wskaŸnik na pocz¹tek listy wybuchów.
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 */
void drawExplosion(Explosion** explosions, ALLEGRO_BITMAP* gameDisplay);

/**
 * @brief Zwalnia pamiêæ zajêt¹ przez wybuchy.
 *
 * Funkcja usuwa wszystkie wybuchy z listy wybuchów i zwalnia zajêt¹ przez nie pamiêæ.
 *
 * @param explosions Podwójny wskaŸnik na pocz¹tek listy wybuchów.
 */
void endExplosions(Explosion** explosions);

#endif /* EXPLOSION_H */