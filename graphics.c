#include "graphics.h"


ALLEGRO_BITMAP* bombGraphic = NULL;
ALLEGRO_BITMAP* DblockGraphic = NULL;
ALLEGRO_BITMAP* hardDblockGraphic = NULL;
ALLEGRO_BITMAP* IDblockGraphic = NULL;
ALLEGRO_BITMAP* heartGraphic = NULL;
ALLEGRO_BITMAP* shieldGraphic = NULL;

ALLEGRO_BITMAP* powerHealthGraphic = NULL;
ALLEGRO_BITMAP* powerBombPowerUpGraphic = NULL;
ALLEGRO_BITMAP* powerBombPowerDownGraphic = NULL;
ALLEGRO_BITMAP* powerVelocityUpGraphic = NULL;
ALLEGRO_BITMAP* powerVelocityDownGraphic = NULL;
ALLEGRO_BITMAP* powerBombLimitUpGraphic = NULL;
ALLEGRO_BITMAP* powerBombLimitDownGraphic = NULL;
ALLEGRO_BITMAP* powerShieldGraphic = NULL;
ALLEGRO_BITMAP* powerInvisibilityGraphic = NULL;
ALLEGRO_BITMAP* powerKickGraphic = NULL;
ALLEGRO_BITMAP* powerBombThiefGraphic = NULL;
ALLEGRO_BITMAP* powerRandomTeleportGraphic = NULL;

void loadGraphics() {   
    bombGraphic = al_load_bitmap("graphics/bomb.png");
    DblockGraphic = al_load_bitmap("graphics/Dblock.png");
    hardDblockGraphic = al_load_bitmap("graphics/hardDblock.png");
    IDblockGraphic = al_load_bitmap("graphics/IDblock.png");
    heartGraphic = al_load_bitmap("graphics/heart.png");
    shieldGraphic = al_load_bitmap("graphics/shield.png"); ;

    powerHealthGraphic = al_load_bitmap("graphics/powers/PWR_HEALTH.png");
    powerBombPowerUpGraphic = al_load_bitmap("graphics/powers/PWR_BOMB_POWER_UP.png");
    powerBombPowerDownGraphic = al_load_bitmap("graphics/powers/PWR_BOMB_POWER_DOWN.png");
    powerVelocityUpGraphic = al_load_bitmap("graphics/powers/PWR_VELOCITY_UP.png");
    powerVelocityDownGraphic = al_load_bitmap("graphics/powers/PWR_VELOCITY_DOWN.png");
    powerBombLimitUpGraphic = al_load_bitmap("graphics/powers/PWR_BOMB_LIMIT_UP.png");
    powerBombLimitDownGraphic = al_load_bitmap("graphics/powers/PWR_BOMB_LIMIT_DOWN.png");
    powerShieldGraphic = al_load_bitmap("graphics/powers/PWR_SHIELD.png");
    powerInvisibilityGraphic = al_load_bitmap("graphics/powers/PWR_INVISIBILITY.png");
    powerKickGraphic = al_load_bitmap("graphics/powers/PWR_KICK.png");
    powerBombThiefGraphic = al_load_bitmap("graphics/powers/PWR_BOMB_THIEF.png");
    powerRandomTeleportGraphic = al_load_bitmap("graphics/powers/PWR_RANDOM_TELEPORT.png");
}