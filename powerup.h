#ifndef POWERUP_H
#define POWERUP_H

#include <allegro5/allegro.h>
#include "position.h"
#include "player.h"
#include "bomb.h"

typedef enum {
    HEALTH,
    BOMB_POWER_UP,
    BOMB_POWER_DOWN,
    VELOCITY_UP,
    VELOCITY_DOWN,
    BOMB_LIMIT_UP,
    BOMB_LIMIT_DOWN,
    TYPES_NUMBER // FLAGA , ILE JEST TYPOW POWER UP
} PowerUpType;

typedef struct PowerUp {
    Position position;
    PowerUpType type;
    ALLEGRO_BITMAP* graphic;
    struct PowerUp* next;
} PowerUp;

void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs);
void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay);
void collectPowerUp(Player* players, int playerNumber, PowerUp** powerUps);
void destroyPowerUp(PowerUp** powerUps, PowerUp* powerUp);

#endif // POWERUP_H