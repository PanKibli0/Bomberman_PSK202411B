#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>

/**
 * @file graphics.h
 * @brief Deklaracje funkcji odpowiedzialnych za ³adowanie grafik w grze Bomberman.
 */

 /**
  * @brief WskaŸnik na bitmapê reprezentuj¹c¹ bombê.
  */
extern ALLEGRO_BITMAP* bombGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ blok zwyk³y.
 */
extern ALLEGRO_BITMAP* DblockGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ twardy blok.
 */
extern ALLEGRO_BITMAP* hardDblockGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ blok nietykalny.
 */
extern ALLEGRO_BITMAP* IDblockGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ serce.
 */
extern ALLEGRO_BITMAP* heartGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ tarczê.
 */
extern ALLEGRO_BITMAP* shieldGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ eksplozjê.
 */
extern ALLEGRO_BITMAP* explosionGraphic;

/**
 * @brief Tablica wskaŸników na bitmapy reprezentuj¹ce spoczywanie graczy.
 */
extern ALLEGRO_BITMAP* playerIdleGraphics[];

/**
 * @brief Tablica wskaŸników na bitmapy reprezentuj¹ce ruch graczy.
 */
extern ALLEGRO_BITMAP* playerGraphics[4][4][4];

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ kopniêcie.
 */
extern ALLEGRO_BITMAP* kickGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ z³odzieja.
 */
extern ALLEGRO_BITMAP* thiefGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ teleportacjê.
 */
extern ALLEGRO_BITMAP* teleportGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ bazow¹ moc.
 */
extern ALLEGRO_BITMAP* powerBaseGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ ulepszenie zdrowia.
 */
extern ALLEGRO_BITMAP* powerHealthGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ ulepszenie si³y bomby.
 */
extern ALLEGRO_BITMAP* powerBombPowerUpGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ os³abienie si³y bomby.
 */
extern ALLEGRO_BITMAP* powerBombPowerDownGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ ulepszenie prêdkoœci.
 */
extern ALLEGRO_BITMAP* powerVelocityUpGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ os³abienie prêdkoœci.
 */
extern ALLEGRO_BITMAP* powerVelocityDownGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ ulepszenie limitu bomb.
 */
extern ALLEGRO_BITMAP* powerBombLimitUpGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ os³abienie limitu bomb.
 */
extern ALLEGRO_BITMAP* powerBombLimitDownGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ os³onê.
 */
extern ALLEGRO_BITMAP* powerShieldGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ niewidzialnoœæ.
 */
extern ALLEGRO_BITMAP* powerInvisibilityGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ kopniêcie.
 */
extern ALLEGRO_BITMAP* powerKickGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ kradzie¿ bomb.
 */
extern ALLEGRO_BITMAP* powerBombThiefGraphic;

/**
 * @brief WskaŸnik na bitmapê reprezentuj¹c¹ losow¹ teleportacjê.
 */
extern ALLEGRO_BITMAP* powerRandomTeleportGraphic;

/**
 * @brief Funkcja odpowiedzialna za ³adowanie grafik.
 */
void loadGraphics();

/**
 * @brief Funkcja odpowiedzialna za ³adowanie grafik graczy.
 *
 * @param playerNumber Liczba graczy w grze.
 */
void loadPlayerGraphics(int playerNumber);

#endif /* GRAPHICS_H */