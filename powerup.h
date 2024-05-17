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
    SHIELD,
    INVISIBILITY,
    KICK,
    BOMB_THIEF,
    RANDOM_TELEPORT,
    TYPES_NUMBER // FLAGA , ILE JEST TYPOW POWER UP
} PowerUpType;

typedef struct PowerUp {
    Position position;
    PowerUpType type;
    float lifeTime;
    ALLEGRO_BITMAP* graphic;
    struct PowerUp* next;
} PowerUp;

void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs);
void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay);
void collectPowerUp(Player* players, int playerNumber, PowerUp** powerUps);
void disappearancePowerUp(PowerUp** powerUps);
void destroyPowerUp(PowerUp** powerUps, PowerUp* powerUp);
void usePower(Player* players, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* blocks, Bomb* bombs, PowerUp* powerUps);
void powerBombThief(Player* player, Bomb* bombs);
void powerTeleport(Player* player, Block* blocks, Bomb* bombs, PowerUp* powerUps);


#endif // POWERUP_H