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
bool checkBlockCollision(float x, float y, Block* block);

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
bool checkBombCollision(float x, float y, Bomb* bomb);

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
bool checkPlayerCollision(float x, float y, Player* players, int playerNumber, int currentPlayerIndex);

#endif /* COLLISION_H */