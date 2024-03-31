#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "position.h"
#include "player.h"
//#include "bomb.h"


// FUNKCJE GRACZA
void initPlayer(Player* player, ALLEGRO_BITMAP* playerGraphic, int x, int y, int velocity, int bomb, ALLEGRO_COLOR color, int controlKeys[5]) {
	player->position.x = x;
	player->position.y = y;
	player->playerGraphic = playerGraphic;
	player->velocity = velocity;
	player->bomb = bomb;
	player->color = color;

	for (int i = 0; i < 5; i++) {
		player->controlKeys[i] = controlKeys[i];
	};

}

void drawPlayer(Player* player) {
	al_draw_filled_circle(player->position.x, player->position.y, 30, player->color); 
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
	else if (al_key_down(keyState, player->controlKeys[4]) && player->bomb>0) {
	}
}