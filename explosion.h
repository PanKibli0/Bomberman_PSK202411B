#ifndef EXPLODE_H
#define EXPLODE_H

#include "position.h"
#include "player.h"
#include "bomb.h"
#include "block.h"

typedef struct Explosion {
	Position position;
	struct Explosion* next;
	int direction;
	ALLEGRO_BITMAP* graphic;
} Explosion;

// FUKCJE

void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber);
//void drawExplosion();

#endif /* EXPLODE_H */