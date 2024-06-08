#include "config.h"
#include "player.h"
#include "bomb.h"
#include "block.h"
/**
 * @file collision.c
 * @brief Plik sprawdzaj¹cy kolizjê podczas rozgrywki.
 */
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
bool checkBlockCollision(float x, float y, Block* block) {
    for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
        if (x + TILE - 6 > blockElement->position.x && x + 6 < blockElement->position.x + TILE &&
            y + TILE - 6 > blockElement->position.y && y + 6 < blockElement->position.y + TILE) {
            return true;
        }
    }
    return false;
}

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
bool checkBombCollision(float x, float y, Bomb* bomb) {
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        if (x + TILE - 6 > bombElement->position.x && x + 6 < bombElement->position.x + TILE &&
            y + TILE - 6 > bombElement->position.y && y + 6 < bombElement->position.y + TILE) {
            return true;
        }
    }
    return false;
}

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
bool checkPlayerCollision(float x, float y, Player* players, int playerNumber, int currentPlayerIndex) {
    for (int i = 0; i < playerNumber; ++i) {
        if (i != currentPlayerIndex) {
            if (players[i].health > 0) {
                if (x + TILE - 6 > players[i].position.x && x + 6 < players[i].position.x + TILE &&
                    y + TILE - 6 > players[i].position.y && y + 6 < players[i].position.y + TILE) {
                    return true;
                }
            }
        }
    }
    return false;
}