#include "infoPanel.h"
#include "graphics.h"

extern ALLEGRO_FONT* font;

void drawInfoPanel(ALLEGRO_BITMAP* infoPanel, Player* players, int playerNumber) {
    int width = 4 * TILE;
    int height = al_get_bitmap_height(infoPanel) * 0.9;
    int objectColor[3][3] = { {255,175,200}, {0,0,0}, {255,127,127} };
    int objectColor2[3][3] = { { 245,0,90 }, {255,255,255}, {255,64,0} };
    int spot = width / 10;
    ALLEGRO_BITMAP** playerInfo = malloc(playerNumber * sizeof(ALLEGRO_BITMAP*));
    for (int i = 0; i < playerNumber; i++) {
        playerInfo[i] = al_create_bitmap(width, height);
        al_set_target_bitmap(playerInfo[i]);
        al_clear_to_color(players[i].color);
        
        

        for (int j = 0; j < 3; j++) {
            
            switch (j) {
            case 0: {
                al_draw_scaled_bitmap(heartGraphic, 0, 0, al_get_bitmap_width(heartGraphic), al_get_bitmap_height(heartGraphic), spot * (1 + 3 * j), spot, TILE/1.25, TILE/1.25, 0);
                al_draw_textf(font, al_map_rgb(255,255,255), spot * (1 + 3 * j) + spot, 0.5 * height / 2 + al_get_font_line_height(font) / 2, ALLEGRO_ALIGN_CENTER, "%d", players[i].health);

                break;
            }
            case 1: {  
                int bombAmount = players[i].bombs.bombAmount;
                if (players[i].activePower.bombThief.hold) {
                    bombAmount--;
                };
                
                al_draw_scaled_bitmap(bombGraphic, 0, 0, al_get_bitmap_width(bombGraphic), al_get_bitmap_height(bombGraphic), spot * (1 + 3 * j), spot, TILE/1.25, TILE/1.25, 0);
                al_draw_textf(font, al_map_rgb(255, 127, 0), spot * (1 + 3 * j) + spot, 0.5 * height / 2 + al_get_font_line_height(font) / 2, ALLEGRO_ALIGN_CENTER, "%d", bombAmount); 

                break;
            }
            case 2: {
                al_draw_filled_rectangle(spot * (1 + 3 * j), spot, spot * (3 + 3 * j), height - spot, al_map_rgb(255,127,127));
                al_draw_rectangle(spot * (1 + 3 * j), spot, spot * (3 + 3 * j), height - spot, al_map_rgb(255,64,0), 6);
                al_draw_textf(font, al_map_rgb(255,255,255), spot * (1 + 3 * j) + spot, 0.5 * height / 2 + al_get_font_line_height(font) / 2, ALLEGRO_ALIGN_CENTER, "%d", players[i].bombs.BombPower);

                break;
            }
            };
        }
        

        al_set_target_bitmap(infoPanel);
        al_draw_bitmap(playerInfo[i], i * TILE * 5, 0.05 * height, 0);
    }

    for (int i = 0; i < playerNumber; i++) {
        al_destroy_bitmap(playerInfo[i]);
    }
    free(playerInfo);
}