#ifndef GAME_H
#define GAME_H
/**
 * @file game.h
 * @brief Plik zawieraj¹cy g³ówn¹ funkcjê, któr¹ wywo³uje.
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>

#include "player.h"
#include "config.h"
#include "bomb.h"
#include "block.h"
#include "collision.h"
#include "explosion.h"
#include "map.h"
#include "infoPanel.h"
#include "powerup.h"
#include "graphics.h"

 /**
  * @brief Funkcja g³ówna gry.
  *
  * G³ówna funkcja gry, która zarz¹dza ca³ym przebiegiem rozgrywki. Odpowiada
  * za inicjalizacjê gry, obs³ugê interakcji z graczami, ruchy, wybuchy, kolizje,
  * aktualizacjê stanu gry oraz rysowanie wszystkich elementów na ekranie.
  *
  * @param playerNumber Liczba graczy bior¹cych udzia³ w grze.
  * @param map Numer mapy, któr¹ ma byæ za³adowana.
  * @param gamework WskaŸnik do zmiennej okreœlaj¹cej czy gra powinna siê toczyæ.
  */
void game(int playerNumber, int map, bool* gamework);

#endif /* GAME_H */