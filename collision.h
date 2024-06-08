#ifndef COLLISION_H
#define COLLISION_H
/**
 * @file collision.h
 * @brief Plik implementacji kolizji gracza podczas gry.
 */
#include "player.h"
#include "bomb.h"
#include "block.h"

 /**
  * @brief Sprawdza kolizjê z blokiem.
  *
  * Funkcja sprawdza, czy podane wspó³rzêdne (x, y) koliduj¹ z którymœ z bloków
  * w liœcie bloków.
  *
  * @param x Wspó³rzêdna x do sprawdzenia.
  * @param y Wspó³rzêdna y do sprawdzenia.
  * @param block WskaŸnik na pocz¹tek listy bloków na planszy.
  * @return true jeœli nast¹pi³a kolizja, false w przeciwnym wypadku.
  */
bool checkBlockCollision(float x, float y, Block* block);

/**
 * @brief Sprawdza kolizjê z bomb¹.
 *
 * Funkcja sprawdza, czy podane wspó³rzêdne (x, y) koliduj¹ z któr¹œ z bomb
 * w liœcie bomb.
 *
 * @param x Wspó³rzêdna x do sprawdzenia.
 * @param y Wspó³rzêdna y do sprawdzenia.
 * @param bomb WskaŸnik na pocz¹tek listy bomb na planszy.
 * @return true jeœli nast¹pi³a kolizja, false w przeciwnym wypadku.
 */
bool checkBombCollision(float x, float y, Bomb* bomb);

/**
 * @brief Sprawdza kolizjê z innym graczem.
 *
 * Funkcja sprawdza, czy podane wspó³rzêdne (x, y) koliduj¹ z którymœ z graczy
 * z wyj¹tkiem gracza o indeksie currentPlayerIndex.
 *
 * @param x Wspó³rzêdna x do sprawdzenia.
 * @param y Wspó³rzêdna y do sprawdzenia.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param currentPlayerIndex Indeks aktualnego gracza, którego kolizje maj¹ byæ pominiête.
 * @return true jeœli nast¹pi³a kolizja, false w przeciwnym wypadku.
 */
bool checkPlayerCollision(float x, float y, Player* players, int playerNumber, int currentPlayerIndex);

#endif /* COLLISION_H */