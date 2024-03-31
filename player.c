#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "position.h"
#include "player.h"
#include "bomb.h"


// FUNKCJE GRACZA
void initPlayer(Player* player, int x, int y, int velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]) {
	player->position.x = x;
	player->position.y = y;
	player->velocity = velocity;
	player->bombs.bombAmount = bombAmount;
	player->bombs.bombTime = bombTime;
	player->bombs.BombPower = bombPower;
	player->color = color;

	for (int i = 0; i < 5; i++) {
		player->controlKeys[i] = controlKeys[i];
	};

	player->playerGraphic = al_create_bitmap(40, 40);
	al_set_target_bitmap(player->playerGraphic);
	al_draw_rectangle(0,0, 40, 40, player->color, 10);
}

void drawPlayer(Player* player, ALLEGRO_DISPLAY* display) {
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(player->playerGraphic, player->position.x, player->position.y, 0);
}



void movePlayer(Player* player, ALLEGRO_KEYBOARD_STATE* keyState) {
	if (al_key_down(keyState, player->controlKeys[0]))
		player->position.y -= player->velocity;
	else if (al_key_down(keyState, player->controlKeys[1]))
		player->position.y += player->velocity;
	else if (al_key_down(keyState, player->controlKeys[2]))
		player->position.x += player->velocity;
	else if (al_key_down(keyState, player->controlKeys[3]))
		player->position.x -= player->velocity;
}



void placeBomb(Player* player, Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState) {
	if (al_key_down(keyState, player->controlKeys[4]) && player->bombs.bombAmount > 0) {
		// Sprawdzanie, czy w danym miejscu na mapie nie ma ju¿ bomby
		for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
			if (bombElement->position.x == player->position.x && bombElement->position.y == player->position.y) {
				// Jeœli w danym miejscu ju¿ jest bomba, przerywamy funkcjê
				return;
			}
		}

		// Jeœli w danym miejscu nie ma bomby, dodajemy now¹
		if ( addBomb(bomb, player->position.x, player->position.y, player->bombs.BombPower, player->bombs.bombTime))
		player->bombs.bombAmount -= 1;

		printf("BOMBS: %d", player->bombs.bombAmount);
	}
}