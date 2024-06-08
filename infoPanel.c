#include "infoPanel.h"
#include "graphics.h"

extern ALLEGRO_FONT* font;

/**
 * @file infoPanel.c
 * @brief Deklaracja funkcji odpowiedzialnych za rysowanie panelu informacyjnego dla graczy w grze Bomberman.
 */

 /**
  * @brief Funkcja odpowiedzialna za rysowanie panelu informacyjnego dla graczy.
  *
  * Rysuje informacje o zdrowiu, iloœci bomb, sile bomb oraz aktywnych power-upach dla ka¿dego gracza na panelu informacyjnym.
  *
  * @param infoPanel Bitmapa panelu informacyjnego.
  * @param players Tablica graczy.
  * @param playerNumber Liczba graczy.
  */
void drawInfoPanel(ALLEGRO_BITMAP* infoPanel, Player* players, int playerNumber) {
    ALLEGRO_BITMAP** playerInfo = malloc(playerNumber * sizeof(ALLEGRO_BITMAP*));
    for (int i = 0; i < playerNumber; i++) {
        playerInfo[i] = al_create_bitmap(340, 130);
        al_set_target_bitmap(playerInfo[i]);

        al_draw_filled_rounded_rectangle(0, 0, 340, 130, 10, 10, players[i].color);

        if (players[i].health > 0) {
            al_draw_scaled_bitmap(heartGraphic, 0, 0, al_get_bitmap_width(bombGraphic), al_get_bitmap_height(bombGraphic), 45, 10, 50, 50, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 125, 20, ALLEGRO_ALIGN_CENTER, "%d", players[i].health);

            int bombAmount = players[i].bombs.bombAmount;
            if (players[i].activePower.bombThief.hold) {
                bombAmount--;
            };

            al_draw_scaled_bitmap(bombGraphic, 0, 0, al_get_bitmap_width(bombGraphic), al_get_bitmap_height(bombGraphic), 200, 11, 50, 50, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 275, 20, ALLEGRO_ALIGN_CENTER, "%d", bombAmount);

            al_draw_scaled_bitmap(explosionGraphic, 0, 0, al_get_bitmap_width(explosionGraphic), al_get_bitmap_height(explosionGraphic), 45, 70, 50, 50, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 125, 80, ALLEGRO_ALIGN_CENTER, "%d", players[i].bombs.BombPower);

            if (players[i].activePower.kick) {
                al_draw_scaled_bitmap(kickGraphic, 0, 0, al_get_bitmap_width(kickGraphic), al_get_bitmap_height(kickGraphic), 220, 70, 50, 50, 0);
            }
            else if (players[i].activePower.bombThief.active) {
                al_draw_scaled_bitmap(thiefGraphic, 0, 0, al_get_bitmap_width(thiefGraphic), al_get_bitmap_height(thiefGraphic), 220, 70, 50, 50, 0);
            }
            else if (players[i].activePower.bombThief.hold) {
                al_draw_scaled_bitmap(thiefGraphic, 0, 0, al_get_bitmap_width(thiefGraphic), al_get_bitmap_height(thiefGraphic), 200, 70, 50, 50, 0);
                al_draw_scaled_bitmap(bombGraphic, 0, 0, al_get_bitmap_width(bombGraphic), al_get_bitmap_height(bombGraphic), 240, 70, 50, 50, 0);
            }
            else if (players[i].activePower.randomTeleport) {
                al_draw_scaled_bitmap(teleportGraphic, 0, 0, al_get_bitmap_width(teleportGraphic), al_get_bitmap_height(teleportGraphic), 220, 70, 50, 50, 0);
            }
            else {
                al_draw_text(font, al_map_rgb(255, 255, 255), 240, 80, ALLEGRO_ALIGN_CENTER, "X");
            }
        }
        else {
            al_draw_text(font, al_map_rgb(255, 255, 255), 170, 46, ALLEGRO_ALIGN_CENTER, "DEAD");
        }

        al_set_target_bitmap(infoPanel);
        al_draw_bitmap(playerInfo[i], i * TILE * 5, 6, 0);
    }

    for (int i = 0; i < playerNumber; i++) {
        al_destroy_bitmap(playerInfo[i]);
    }
    free(playerInfo);
}

