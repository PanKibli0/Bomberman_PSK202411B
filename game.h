#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>


#include "player.h"
#include "config.h"
#include "bomb.h"
#include "block.h"
#include "collision.h"
#include "explosion.h"
#include "map.h"
#include "infoPanel.h"
#include "powerup.h"
#include "graphics.h"

void game(int playerNumber, int map);

#endif /* GAME_H */