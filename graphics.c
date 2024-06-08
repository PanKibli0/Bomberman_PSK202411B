/**
 * @file graphics.c
 * @brief Plik implementacji modu³u graficznego.
 */

#include "graphics.h"
#include <stdio.h>

 // Zmienne graficzne
ALLEGRO_BITMAP* bombGraphic = NULL; /**< Bitmapa dla grafiki bomby. */
ALLEGRO_BITMAP* DblockGraphic = NULL; /**< Bitmapa dla grafiki bloku D. */
ALLEGRO_BITMAP* hardDblockGraphic = NULL; /**< Bitmapa dla grafiki twardego bloku D. */
ALLEGRO_BITMAP* IDblockGraphic = NULL; /**< Bitmapa dla grafiki bloku ID. */
ALLEGRO_BITMAP* heartGraphic = NULL; /**< Bitmapa dla grafiki serca. */
ALLEGRO_BITMAP* shieldGraphic = NULL; /**< Bitmapa dla grafiki tarczy. */
ALLEGRO_BITMAP* explosionGraphic = NULL; /**< Bitmapa dla grafiki eksplozji. */

ALLEGRO_BITMAP* playerIdleGraphics[4] = { NULL }; /**< Tablica bitmap dla grafiki spoczynku gracza. */
ALLEGRO_BITMAP* playerGraphics[4][4][4] = { NULL }; /**< Trójwymiarowa tablica bitmap dla grafiki gracza. */

ALLEGRO_BITMAP* kickGraphic = NULL; /**< Bitmapa dla grafiki kopniêcia. */
ALLEGRO_BITMAP* thiefGraphic = NULL; /**< Bitmapa dla grafiki z³odzieja. */
ALLEGRO_BITMAP* teleportGraphic = NULL; /**< Bitmapa dla grafiki teleportu. */

ALLEGRO_BITMAP* powerBaseGraphic = NULL; /**< Bitmapa dla podstawowej grafiki bonusu. */
ALLEGRO_BITMAP* powerHealthGraphic = NULL; /**< Bitmapa dla grafiki bonusu zdrowia. */
ALLEGRO_BITMAP* powerBombPowerUpGraphic = NULL; /**< Bitmapa dla grafiki bonusu zwiêkszenia mocy bomby. */
ALLEGRO_BITMAP* powerBombPowerDownGraphic = NULL; /**< Bitmapa dla grafiki bonusu zmniejszenia mocy bomby. */
ALLEGRO_BITMAP* powerVelocityUpGraphic = NULL; /**< Bitmapa dla grafiki bonusu zwiêkszenia prêdkoœci. */
ALLEGRO_BITMAP* powerVelocityDownGraphic = NULL; /**< Bitmapa dla grafiki bonusu zmniejszenia prêdkoœci. */
ALLEGRO_BITMAP* powerBombLimitUpGraphic = NULL; /**< Bitmapa dla grafiki bonusu zwiêkszenia limitu bomb. */
ALLEGRO_BITMAP* powerBombLimitDownGraphic = NULL; /**< Bitmapa dla grafiki bonusu zmniejszenia limitu bomb. */
ALLEGRO_BITMAP* powerShieldGraphic = NULL; /**< Bitmapa dla grafiki bonusu tarczy. */
ALLEGRO_BITMAP* powerInvisibilityGraphic = NULL; /**< Bitmapa dla grafiki bonusu niewidzialnoœci. */
ALLEGRO_BITMAP* powerKickGraphic = NULL; /**< Bitmapa dla grafiki bonusu kopniêcia. */
ALLEGRO_BITMAP* powerBombThiefGraphic = NULL; /**< Bitmapa dla grafiki bonusu z³odzieja bomb. */
ALLEGRO_BITMAP* powerRandomTeleportGraphic = NULL; /**< Bitmapa dla grafiki bonusu losowego teleportu. */

/**
 * @brief Funkcja ³adowania grafiki.
 *
 * £aduje wszystkie bitmapy u¿ywane w grze.
 */
void loadGraphics() {
    bombGraphic = al_load_bitmap("graphics/bomb.png");
    DblockGraphic = al_load_bitmap("graphics/Dblock.png");
    hardDblockGraphic = al_load_bitmap("graphics/hardDblock.png");
    IDblockGraphic = al_load_bitmap("graphics/IDblock.png");
    heartGraphic = al_load_bitmap("graphics/heart.png");
    shieldGraphic = al_load_bitmap("graphics/shield.png");
    explosionGraphic = al_load_bitmap("graphics/explosion.png");

    char filename[50];
    const char* folder = "graphics/player%d/idle.png";
    for (int character = 0; character < 4; character++) {
        snprintf(filename, sizeof(filename), folder, character + 1);
        playerIdleGraphics[character] = al_load_bitmap(filename);
    }

    kickGraphic = al_load_bitmap("graphics/kick.png");
    thiefGraphic = al_load_bitmap("graphics/thief.png");
    teleportGraphic = al_load_bitmap("graphics/teleport.png");

    powerBaseGraphic = al_load_bitmap("graphics/powers/PWR_BASE.png");
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
    powerBombThiefGraphic = al_load_bitmap("graphics/powers/PWR_THIEF.png");
    powerRandomTeleportGraphic = al_load_bitmap("graphics/powers/PWR_TELEPORT.png");
}

/**
 * @brief Funkcja ³adowania grafiki gracza.
 *
 * £aduje bitmapy grafiki gracza.
 *
 * @param playerNumber Liczba graczy.
 */
void loadPlayerGraphics(int playerNumber) {
    char filename[50];
    const char* folder = "graphics/player%d/%s%d.png"; // Format nazwy pliku: "graphics/player%d/direction%d.png"

    for (int character = 0; character < playerNumber; character++) {
        for (int direction = 0; direction < 4; direction++) {
            for (int frame = 1; frame <= 4; frame++) {
                snprintf(filename, sizeof(filename), folder, character + 1,
                    (direction == 0) ? "up" : ((direction == 1) ? "down" :
                        ((direction == 2) ? "right" : "left")), frame);
                playerGraphics[character][direction][frame - 1] = al_load_bitmap(filename);
            }
        }
    }
}