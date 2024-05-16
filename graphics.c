#include "graphics.h"

ALLEGRO_BITMAP* bombGraphic = NULL;
ALLEGRO_BITMAP* DblockGraphic = NULL;
ALLEGRO_BITMAP* hardDblockGraphic = NULL;
ALLEGRO_BITMAP* IDblockGraphic = NULL;
ALLEGRO_BITMAP* heartGraphic = NULL;



void loadGraphics() {
	bombGraphic = al_load_bitmap("graphics/bomb.png");
	DblockGraphic = al_load_bitmap("graphics/Dblock.png");
	hardDblockGraphic = al_load_bitmap("graphics/hardDblock.png");
	IDblockGraphic = al_load_bitmap("graphics/IDblock.png");
	heartGraphic = al_load_bitmap("graphics/heart.png");
}