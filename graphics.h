#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>

/**
 * @file graphics.h
 * @brief Deklaracje funkcji odpowiedzialnych za �adowanie grafik w grze Bomberman.
 */

 /**
  * @brief Wska�nik na bitmap� reprezentuj�c� bomb�.
  */
extern ALLEGRO_BITMAP* bombGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� blok zwyk�y.
 */
extern ALLEGRO_BITMAP* DblockGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� twardy blok.
 */
extern ALLEGRO_BITMAP* hardDblockGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� blok nietykalny.
 */
extern ALLEGRO_BITMAP* IDblockGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� serce.
 */
extern ALLEGRO_BITMAP* heartGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� tarcz�.
 */
extern ALLEGRO_BITMAP* shieldGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� eksplozj�.
 */
extern ALLEGRO_BITMAP* explosionGraphic;

/**
 * @brief Tablica wska�nik�w na bitmapy reprezentuj�ce spoczywanie graczy.
 */
extern ALLEGRO_BITMAP* playerIdleGraphics[];

/**
 * @brief Tablica wska�nik�w na bitmapy reprezentuj�ce ruch graczy.
 */
extern ALLEGRO_BITMAP* playerGraphics[4][4][4];

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� kopni�cie.
 */
extern ALLEGRO_BITMAP* kickGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� z�odzieja.
 */
extern ALLEGRO_BITMAP* thiefGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� teleportacj�.
 */
extern ALLEGRO_BITMAP* teleportGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� bazow� moc.
 */
extern ALLEGRO_BITMAP* powerBaseGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� ulepszenie zdrowia.
 */
extern ALLEGRO_BITMAP* powerHealthGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� ulepszenie si�y bomby.
 */
extern ALLEGRO_BITMAP* powerBombPowerUpGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� os�abienie si�y bomby.
 */
extern ALLEGRO_BITMAP* powerBombPowerDownGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� ulepszenie pr�dko�ci.
 */
extern ALLEGRO_BITMAP* powerVelocityUpGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� os�abienie pr�dko�ci.
 */
extern ALLEGRO_BITMAP* powerVelocityDownGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� ulepszenie limitu bomb.
 */
extern ALLEGRO_BITMAP* powerBombLimitUpGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� os�abienie limitu bomb.
 */
extern ALLEGRO_BITMAP* powerBombLimitDownGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� os�on�.
 */
extern ALLEGRO_BITMAP* powerShieldGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� niewidzialno��.
 */
extern ALLEGRO_BITMAP* powerInvisibilityGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� kopni�cie.
 */
extern ALLEGRO_BITMAP* powerKickGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� kradzie� bomb.
 */
extern ALLEGRO_BITMAP* powerBombThiefGraphic;

/**
 * @brief Wska�nik na bitmap� reprezentuj�c� losow� teleportacj�.
 */
extern ALLEGRO_BITMAP* powerRandomTeleportGraphic;

/**
 * @brief Funkcja odpowiedzialna za �adowanie grafik.
 */
void loadGraphics();

/**
 * @brief Funkcja odpowiedzialna za �adowanie grafik graczy.
 *
 * @param playerNumber Liczba graczy w grze.
 */
void loadPlayerGraphics(int playerNumber);

#endif /* GRAPHICS_H */