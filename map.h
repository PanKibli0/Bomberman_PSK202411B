#ifndef MAP_H
#define MAP_H

#include "block.h"
#include "config.h"
#include "player.h"

/**
 * @file map.h
 * @brief Deklaracja funkcji odpowiedzialnych za generowanie uk�adu mapy w grze Bomberman.
 */

 /**
  * @brief Funkcja generuj�ca uk�ad mapy.
  *
  * Generuje uk�ad mapy na podstawie zdefiniowanego indeksu mapy.
  * Tworzy bloki, umieszcza graczy na mapie oraz ustala szans� na pojawienie si� power-up�w.
  *
  * @param blocks Tablica wska�nik�w na bloki.
  * @param players Tablica graczy.
  * @param playerNumber Liczba graczy.
  * @param mapIndex Indeks mapy.
  * @param CHANCE Wska�nik na zmienn� przechowuj�c� szans� na pojawienie si� power-up�w.
  */
void mapLayout(Block** blocks, Player* players, int playerNumber, int mapIndex, int* CHANCE);

#endif /* MAP_H */