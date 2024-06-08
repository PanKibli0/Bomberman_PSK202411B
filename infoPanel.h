#ifndef INFO_H
#define INFO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"

/**
 * @file infoPanel.h
 * @brief Plik wywo³uj¹cy funkcjê rysuj¹c¹ panel informacyjny.
 */

 /**
  * @brief Funkcja odpowiedzialna za rysowanie panelu informacyjnego.
  *
  * @param infoPanel Bitmapa panelu informacyjnego.
  * @param players Tablica graczy.
  * @param playerNumber Liczba graczy.
  */
void drawInfoPanel(ALLEGRO_BITMAP* infoPanel, Player* players, int playerNumber);

#endif /* INFO_H */