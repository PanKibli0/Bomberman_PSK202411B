#ifndef GAME_H
#define GAME_H
/**
 * @file game.h
 * @brief Plik zawieraj�cy g��wn� funkcj�, kt�r� wywo�uje.
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
  * @brief Funkcja g��wna gry.
  *
  * G��wna funkcja gry, kt�ra zarz�dza ca�ym przebiegiem rozgrywki. Odpowiada
  * za inicjalizacj� gry, obs�ug� interakcji z graczami, ruchy, wybuchy, kolizje,
  * aktualizacj� stanu gry oraz rysowanie wszystkich element�w na ekranie.
  *
  * @param playerNumber Liczba graczy bior�cych udzia� w grze.
  * @param map Numer mapy, kt�r� ma by� za�adowana.
  * @param gamework Wska�nik do zmiennej okre�laj�cej czy gra powinna si� toczy�.
  */
void game(int playerNumber, int map, bool* gamework);

#endif /* GAME_H */