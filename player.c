#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "position.h"
#include "player.h"
#include "block.h"
#include "collision.h"
#include "powerUp.h"

void initPowerUps(Player* player) {
	player->activePower.kick = false; 
	player->activePower.bombThief.active = false;
	player->activePower.bombThief.hold = false;	
	player->activePower.randomTeleport = false;
	player->activePower.invisibility = 0.0;
	player->activePower.shieldTime = 0.0;
}

// FUNKCJE GRACZA
void initPlayer(Player* player, unsigned int health, int x, int y, float velocity, int bombAmount,  int bombPower, ALLEGRO_COLOR color, int controlKeys[6]) {
	player->health = health;
	player->position.x = x;
	player->position.y = y;
	player->velocity = velocity;
	player->bombs.bombAmount = bombAmount;
	player->bombs.BombPower = bombPower;
	player->color = color;
	player->direction = 0;
	initPowerUps(player);

	for (int i = 0; i < 6; i++) {
		player->controlKeys[i] = controlKeys[i];
	};

	player->graphic = al_create_bitmap(TILE, TILE);
	al_set_target_bitmap(player->graphic);
	al_draw_rectangle(0, 0, TILE, TILE, player->color, 10);
}

void drawPlayer(Player* players, int playerNumber, ALLEGRO_BITMAP* gameDisplay) {
	al_set_target_bitmap(gameDisplay);
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].health > 0) {
			al_draw_bitmap(players[i].graphic, players[i].position.x, players[i].position.y, 0);	
			if (players[i].activePower.shieldTime > 0) {
				al_draw_circle(players[i].position.x + TILE / 2, players[i].position.y + TILE / 2, TILE / 1.5, al_map_rgb(0, 162, 232), 5);
			}
		}
	}
}


void movePlayer(Player* players, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, Bomb* bomb) {
	for (int i = 0; i < playerNumber; i++) {
		if (players[i].health > 0) {
			float dx = 0, dy = 0;

			if (al_key_down(keyState, players[i].controlKeys[0])) {
				dy -= players[i].velocity;
				players[i].direction = 1;
			}
			if (al_key_down(keyState, players[i].controlKeys[1])) {
				dy += players[i].velocity;
				players[i].direction = 2;
			}
			if (al_key_down(keyState, players[i].controlKeys[2])) {
				dx += players[i].velocity;
				players[i].direction = 3;
			}
			if (al_key_down(keyState, players[i].controlKeys[3])) {
				dx -= players[i].velocity;
				players[i].direction = 4;
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
				if (!checkBlockCollision(newX, newY,  block) && !checkPlayerCollision(newX, newY, players, playerNumber, i)) {
					players[i].position.x = newX;
					players[i].position.y = newY;
				}
			}
		}
	}
}

