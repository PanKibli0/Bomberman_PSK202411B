#include "infoPanel.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void drawInfoPanel(ALLEGRO_BITMAP* infoPanel, Player* players, int playerNumber) {

    int width = 19 * TILE;
    int height = al_get_bitmap_height(infoPanel);

    ALLEGRO_BITMAP** playerInfo = malloc(playerNumber * sizeof(ALLEGRO_BITMAP*));

    for (int i = 0; i < playerNumber; i++) {
        int color = i * 64;
        playerInfo[i] = al_create_bitmap(4 * TILE, 0.75 * height);
        al_set_target_bitmap(playerInfo[i]);
        al_clear_to_color(players[i].color);

        // Rysowanie pierwszego kó³ka w œrodku bloku
        int circleX1 = al_get_bitmap_width(playerInfo[i]) / 4;
        int circleY = al_get_bitmap_height(playerInfo[i]) / 2;
        int circleRadius = al_get_bitmap_height(playerInfo[i]) / 4;
        al_draw_filled_circle(circleX1, circleY, circleRadius, al_map_rgb(255, 255, 255));

        // Rysowanie drugiego kó³ka w œrodku bloku
        int circleX2 = 3 * al_get_bitmap_width(playerInfo[i]) / 4;
        al_draw_filled_circle(circleX2, circleY, circleRadius, al_map_rgb(255, 255, 255));

        // Wypisanie informacji w œrodku kó³ek
        ALLEGRO_FONT* font = al_create_builtin_font();
        

        // Wypisanie zdrowia w œrodku pierwszego kó³ka
        int textWidth1 = al_get_text_width(font, "Health: %d", players[i].health);
        int textHeight1 = al_get_font_ascent(font);
        al_draw_textf(font, al_map_rgb(0, 0, 0), circleX1 - textWidth1 / 2, circleY - textHeight1 / 2, ALLEGRO_ALIGN_LEFT, "Health: %d", players[i].health);

        // Wypisanie iloœci bomb w œrodku drugiego kó³ka
        int textWidth2 = al_get_text_width(font, "Bombs: %d", players[i].bombs.bombAmount);
        int textHeight2 = al_get_font_ascent(font);
        al_draw_textf(font, al_map_rgb(0, 0, 0), circleX2 - textWidth2 / 2, circleY - textHeight2 / 2, ALLEGRO_ALIGN_LEFT, "Bombs: %d", players[i].bombs.bombAmount);

        al_destroy_font(font);

        al_set_target_bitmap(infoPanel);
        al_draw_bitmap(playerInfo[i], i * TILE * 5, 0.125 * height, 0);
    }

    for (int i = 0; i < playerNumber; i++) {
        al_destroy_bitmap(playerInfo[i]);
    }
    free(playerInfo);
}