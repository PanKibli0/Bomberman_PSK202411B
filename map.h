#ifndef MAP_H
#define MAP_H

#include "block.h"
#include "config.h"
#include "player.h"

/**
 * @file map.h
 * @brief Deklaracja funkcji odpowiedzialnych za generowanie uk³adu mapy w grze Bomberman.
 */

 /**
  * @brief Funkcja generuj¹ca uk³ad mapy.
  *
  * Generuje uk³ad mapy na podstawie zdefiniowanego indeksu mapy.
  * Tworzy bloki, umieszcza graczy na mapie oraz ustala szansê na pojawienie siê power-upów.
  *
  * @param blocks Tablica wskaŸników na bloki.
  * @param players Tablica graczy.
  * @param playerNumber Liczba graczy.
  * @param mapIndex Indeks mapy.
  * @param CHANCE WskaŸnik na zmienn¹ przechowuj¹c¹ szansê na pojawienie siê power-upów.
  */
void mapLayout(Block** blocks, Player* players, int playerNumber, int mapIndex, int* CHANCE);

#endif /* MAP_H */