#ifndef POWERUP_H
#define POWERUP_H

#include <allegro5/allegro.h>
#include "position.h"
#include "player.h"

typedef enum {
    HEALTH,
    BOMB_POWER
} PowerUpType;

typedef struct PowerUp {
    Position position;
    PowerUpType type;
    ALLEGRO_BITMAP* graphic;
    struct PowerUp* next;
} PowerUp;


void createPowerUp(PowerUp** powerUps, int x, int y, PowerUpType type);
void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay);
void collectPowerUp(Player* player, PowerUp** powerUps);


#endif // POWERUP_H