#include "graphics.h"

ALLEGRO_BITMAP* bombGraphic = NULL;

ALLEGRO_BITMAP* dblockGraphic = NULL;
ALLEGRO_BITMAP* idblockGraphic = NULL;
ALLEGRO_BITMAP* heartGraphic = NULL;


void loadGraphics() {
	bombGraphic = al_load_bitmap("graphics/bomb.png");
	dblockGraphic = al_load_bitmap("graphics/dblock.png");
	idblockGraphic = al_load_bitmap("graphics/idblock.png");
	heartGraphic = al_load_bitmap("graphics/heart.png");
}