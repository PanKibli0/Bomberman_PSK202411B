#ifndef BOMB_H
#define BOMB_H

#include <allegro5/allegro.h>
#include "position.h"


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

// FUKCJE
void setBomb(Player* player, int power);


#endif /* BOMB_H */