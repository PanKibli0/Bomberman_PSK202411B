#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>


extern ALLEGRO_BITMAP* bombGraphic;
extern ALLEGRO_BITMAP* DblockGraphic;
extern ALLEGRO_BITMAP* hardDblockGraphic;
extern ALLEGRO_BITMAP* IDblockGraphic;
extern ALLEGRO_BITMAP* heartGraphic;
extern ALLEGRO_BITMAP* shieldGraphic;


extern ALLEGRO_BITMAP* powerHealthGraphic;
extern ALLEGRO_BITMAP* powerBombPowerUpGraphic;
extern ALLEGRO_BITMAP* powerBombPowerDownGraphic;
extern ALLEGRO_BITMAP* powerVelocityUpGraphic;
extern ALLEGRO_BITMAP* powerVelocityDownGraphic;
extern ALLEGRO_BITMAP* powerBombLimitUpGraphic;
extern ALLEGRO_BITMAP* powerBombLimitDownGraphic;
extern ALLEGRO_BITMAP* powerShieldGraphic;
extern ALLEGRO_BITMAP* powerInvisibilityGraphic;
extern ALLEGRO_BITMAP* powerKickGraphic;
extern ALLEGRO_BITMAP* powerBombThiefGraphic;
extern ALLEGRO_BITMAP* powerRandomTeleportGraphic;


void loadGraphics();


#endif /* GRAPHICS_H */