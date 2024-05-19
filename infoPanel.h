#ifndef INFO_H
#define INFO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"


void drawInfoPanel(ALLEGRO_BITMAP* infoPanel, Player* players, int playerNumber);

#endif /* INFO_H */