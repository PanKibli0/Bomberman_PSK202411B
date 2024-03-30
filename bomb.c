#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "position.h"
#include "player.h"

// BOMBA
typedef struct {
	Position position;
	ALLEGRO_BITMAP* playerGraphic;
	int power;
	
} Bomb;

typedef struct {
	Position position;
	ALLEGRO_BITMAP* playerGraphic;
	int direction;
} Explode;

// FUNKCJE BOMBY
void setBomb(Player* player, int power) {
	printf("BOMBA LECI");
	ALLEGRO_BITMAP* bomb = al_create_bitmap(20, 20);
	al_draw_filled_circle(player->position.x, player->position.y, 15, al_map_rgb(200,40,40));
	al_draw_circle(player->position.x, player->position.y, 20, al_map_rgb(255,255,255), 5);
	player->bomb -= 1;
};