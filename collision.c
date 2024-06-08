#include "config.h"
#include "player.h"
#include "bomb.h"
#include "block.h"
/**
 * @file collision.c
 * @brief Plik sprawdzaj�cy kolizj� podczas rozgrywki.
 */
 /**
  * @brief Sprawdza kolizj� z blokiem.
  *
  * Funkcja sprawdza, czy podane wsp�rz�dne (x, y) koliduj� z kt�rym� z blok�w
  * w li�cie blok�w.
  *
  * @param x Wsp�rz�dna x do sprawdzenia.
  * @param y Wsp�rz�dna y do sprawdzenia.
  * @param block Wska�nik na pocz�tek listy blok�w na planszy.
  * @return true je�li nast�pi�a kolizja, false w przeciwnym wypadku.
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
 * @brief Sprawdza kolizj� z bomb�.
 *
 * Funkcja sprawdza, czy podane wsp�rz�dne (x, y) koliduj� z kt�r�� z bomb
 * w li�cie bomb.
 *
 * @param x Wsp�rz�dna x do sprawdzenia.
 * @param y Wsp�rz�dna y do sprawdzenia.
 * @param bomb Wska�nik na pocz�tek listy bomb na planszy.
 * @return true je�li nast�pi�a kolizja, false w przeciwnym wypadku.
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
 * @brief Sprawdza kolizj� z innym graczem.
 *
 * Funkcja sprawdza, czy podane wsp�rz�dne (x, y) koliduj� z kt�rym� z graczy
 * z wyj�tkiem gracza o indeksie currentPlayerIndex.
 *
 * @param x Wsp�rz�dna x do sprawdzenia.
 * @param y Wsp�rz�dna y do sprawdzenia.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param currentPlayerIndex Indeks aktualnego gracza, kt�rego kolizje maj� by� pomini�te.
 * @return true je�li nast�pi�a kolizja, false w przeciwnym wypadku.
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