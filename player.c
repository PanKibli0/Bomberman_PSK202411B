#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

#include "position.h"
#include "player.h"
#include "bomb.h"
#include "block.h"

// FUNKCJE GRACZA
void initPlayer(Player* player,unsigned int health, int x, int y, float velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]) {
	player->health = health;
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

	player->graphic = al_create_bitmap(40, 40);
	al_set_target_bitmap(player->graphic);
	al_draw_rectangle(0,0, 40, 40, player->color, 10);
}

void drawPlayer(Player* player, ALLEGRO_DISPLAY* display) {
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(player->graphic, player->position.x, player->position.y, 0);
}



// -----------------------------------


bool checkCollision(float x, float y, Block* block) {
    for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
        if (x + 40 > blockElement->position.x && x < blockElement->position.x + 40 &&
            y + 40 > blockElement->position.y && y < blockElement->position.y + 40) {
            return true; 
        }
    }
    return false; 
}


void movePlayer(Player* player, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, Bomb* bomb) {
    float dx = 0, dy = 0;

    if (al_key_down(keyState, player->controlKeys[0]))
        dy -= player->velocity;
    if (al_key_down(keyState, player->controlKeys[1]))
        dy += player->velocity;
    if (al_key_down(keyState, player->controlKeys[2]))
        dx += player->velocity;
    if (al_key_down(keyState, player->controlKeys[3]))
        dx -= player->velocity;

    float newX = player->position.x + dx;
    float newY = player->position.y + dy;

    float displacementX = 0;
    float displacementY = 0;

    
    if (!checkCollision(newX, newY, block)) {
        
        player->position.x = newX;
        player->position.y = newY;
    }
    else {
        
        player->position.x += displacementX;
        player->position.y += displacementY;
    }
}

// ----------------------------------------------------

void placeBomb(Player* player, Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState) {
	if (al_key_down(keyState, player->controlKeys[4]) && player->bombs.bombAmount > 0) {
		if ( addBomb(bomb, player->position.x, player->position.y, player->bombs.BombPower, player->bombs.bombTime))
		player->bombs.bombAmount -= 1;

		printf("BOMBS: %d \t", player->bombs.bombAmount);
	}
}

/*
void movePlayer(Player* player, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, Bomb* bomb) {
    float dx = 0, dy = 0;

    if (al_key_down(keyState, player->controlKeys[0]))
        dy -= player->velocity;
    if (al_key_down(keyState, player->controlKeys[1]))
        dy += player->velocity;
    if (al_key_down(keyState, player->controlKeys[2]))
        dx += player->velocity;
    if (al_key_down(keyState, player->controlKeys[3]))
        dx -= player->velocity;

    float newX = player->position.x + dx;
    float newY = player->position.y + dy;

    float displacementX = 0;
    float displacementY = 0;

    if (!checkCollisionWithResolution(newX, newY, &displacementX, &displacementY, block)) {
        player->position.x = newX;
        player->position.y = newY;
    }
    else {
        player->position.x += displacementX;
        player->position.y += displacementY;
    }

    printf("%d %d\n ", player->position.x, player->position.y);
}
*/

/*
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        if (newX + 40 > bombElement->position.x && newX < bombElement->position.x + 40 &&
            newY + 40 > bombElement->position.y && newY < bombElement->position.y + 40) {
            return;
        }
    }
    */