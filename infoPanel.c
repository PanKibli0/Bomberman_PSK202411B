#include "infoPanel.h"

void drawInfo();

void drawInfoPanel(ALLEGRO_BITMAP* infoPanel) {
	al_set_target_bitmap(infoPanel);
	al_clear_to_color(al_map_rgb(255, 252, 171));
}
