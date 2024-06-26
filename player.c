﻿/**
 * @file player.c
 * @brief Główny plik odpowiadający za działanie postaci.
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>

#include "config.h"
#include "player.h"
#include "block.h"
#include "collision.h"
#include "powerUp.h"
#include "graphics.h"

 /**
  * Inicjuje strukturę danych dotyczącą aktywnych power-upów gracza.
  * @param player Wskaźnik na gracza, którego power-upy należy zainicjować
  */
void initPowerUps(Player* player) {
	player->activePower.kick = false;
	player->activePower.bombThief.active = false;
	player->activePower.bombThief.hold = false;
	player->activePower.randomTeleport = false;
	player->activePower.invisibility = 0.0;
	player->activePower.shieldTime = 0.0;
}

/**
 * Inicjuje gracza.
 * @param players Wskaźnik na tablicę graczy
 * @param playerIndex Indeks gracza do zainicjowania
 * @param health Zdrowie początkowe gracza
 * @param x Współrzędna X pozycji startowej gracza
 * @param y Współrzędna Y pozycji startowej gracza
 * @param velocity Prędkość gracza
 * @param bombAmount Ilość bomb, które gracz może postawić jednocześnie
 * @param bombPower Siła eksplozji bomb
 * @param color Kolor gracza
 * @param controlKeys Tablica klawiszy sterowania
 */
void initPlayer(Player* players, int playerIndex, unsigned int health, int x, int y, float velocity, int bombAmount, int bombPower, ALLEGRO_COLOR color, int controlKeys[6]) {
	players[playerIndex].health = health;
	players[playerIndex].position.x = x;
	players[playerIndex].position.y = y;
	players[playerIndex].velocity = velocity;
	players[playerIndex].bombs.bombAmount = bombAmount;
	players[playerIndex].bombs.BombPower = bombPower;
	players[playerIndex].color = color;
	players[playerIndex].direction = 0;
	players[playerIndex].frame = 0;


	initPowerUps(&players[playerIndex]);

	for (int i = 0; i < 6; i++) {
		players[playerIndex].controlKeys[i] = controlKeys[i];
	}
	players[playerIndex].graphic = al_create_bitmap(TILE, TILE);
	al_set_target_bitmap(players[playerIndex].graphic);
	al_draw_scaled_bitmap(playerIdleGraphics[playerIndex], 0, 0, al_get_bitmap_width(playerIdleGraphics[playerIndex]), al_get_bitmap_height(playerIdleGraphics[playerIndex]), 0, 0, TILE, TILE, 0);
}

/**
 * Rysuje graczy na ekranie.
 * @param players Wskaźnik na tablicę graczy
 * @param playerNumber Liczba graczy
 * @param gameDisplay Bitmapa ekranu gry
 */
void drawPlayer(Player* players, int playerNumber, ALLEGRO_BITMAP* gameDisplay) {
	al_set_target_bitmap(gameDisplay);
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].health > 0 && players[i].activePower.invisibility <= 0) {
			al_draw_scaled_bitmap(players[i].graphic, 0, 0, al_get_bitmap_width(players[i].graphic), al_get_bitmap_height(players[i].graphic),
				players[i].position.x, players[i].position.y + 5, TILE - 9, TILE - 9, 0);
			if (players[i].activePower.shieldTime > 0) {
				al_draw_scaled_bitmap(shieldGraphic,
					0, 0, al_get_bitmap_width(shieldGraphic), al_get_bitmap_height(shieldGraphic),
					players[i].position.x + (al_get_bitmap_width(players[i].graphic) - al_get_bitmap_width(shieldGraphic) * 0.75) / 2,
					players[i].position.y + (al_get_bitmap_height(players[i].graphic) - al_get_bitmap_height(shieldGraphic) * 0.75) / 2,
					al_get_bitmap_width(shieldGraphic) * 0.75, al_get_bitmap_height(shieldGraphic) * 0.75, 0);
			}
		}
	}
}

/**
 * Porusza graczy na podstawie stanu klawiatury.
 * @param players Wskaźnik na tablicę graczy
 * @param playerNumber Liczba graczy
 * @param keyState Stan klawiatury
 * @param block Blok
 * @param bomb Bomba
 */
void movePlayer(Player* players, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, Bomb* bomb) {
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].health > 0) {
			float dx = 0, dy = 0;
			bool moved = false;

			if (al_key_down(keyState, players[i].controlKeys[0])) {
				dy -= players[i].velocity;
				players[i].direction = 1; // góra
				moved = true;
			}
			if (al_key_down(keyState, players[i].controlKeys[1])) {
				dy += players[i].velocity;
				players[i].direction = 2; // dół
				moved = true;
			}
			if (al_key_down(keyState, players[i].controlKeys[2])) {
				dx += players[i].velocity;
				players[i].direction = 3; // prawo
				moved = true;
			}
			if (al_key_down(keyState, players[i].controlKeys[3])) {
				dx -= players[i].velocity;
				players[i].direction = 4; // lewo
				moved = true;
			}

			if (moved) {
				players[i].frame++;
				players[i].frame %= 40;
				if (players[i].frame % 10 == 0) players[i].graphic = playerGraphics[i][players[i].direction - 1][players[i].frame / 10];
			}

			float newX = players[i].position.x + dx;
			float newY = players[i].position.y + dy;


			bool onBomb = checkBombCollision(players[i].position.x, players[i].position.y, bomb);

			if (!onBomb) {
				if (!checkBlockCollision(newX, newY, block) && !checkPlayerCollision(newX, newY, players, playerNumber, i) && !checkBombCollision(newX, newY, bomb)) {
					players[i].position.x = newX;
					players[i].position.y = newY;
				}
			}
			else {
				if (!checkBlockCollision(newX, newY, block) && !checkPlayerCollision(newX, newY, players, playerNumber, i)) {
					players[i].position.x = newX;
					players[i].position.y = newY;
				}
			}
		}
	}
}