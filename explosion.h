#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "position.h"
#include "player.h"
#include "block.h"


typedef struct Explosion {
	Position position;
	int direction;
	float time;
	ALLEGRO_BITMAP* graphic;
	struct Explosion* next;
} Explosion;

// FUKCJE

void explosion(struct Bomb* bomb, Block** blocks, Player* players, int playerNumber, Explosion** explosions);
void drawExplosion(Explosion** explosions, ALLEGRO_BITMAP* gameDisplay);
void endExplosions(Explosion** explosions);
#endif /* EXPLOSION_H */