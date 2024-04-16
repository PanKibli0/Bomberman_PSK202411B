#include "infoPanel.h"

void drawInfoPanel(ALLEGRO_BITMAP* infoPanel, Player* players, int playerNumber, ALLEGRO_FONT* font) {
    int width = 4 * TILE;
    int height = al_get_bitmap_height(infoPanel) * 0.9;
    int objectColor[3][3] = { {255,175,200}, {0,0,0}, {255,127,127} };
    int objectColor2[3][3] = { { 245,0,90 }, {255,200,128}, {255,64,0} };
    int spot = width / 10;
    int text = 0;
    ALLEGRO_BITMAP** playerInfo = malloc(playerNumber * sizeof(ALLEGRO_BITMAP*));

    for (int i = 0; i < playerNumber; i++) {
        playerInfo[i] = al_create_bitmap(width, height);
        al_set_target_bitmap(playerInfo[i]);
        al_clear_to_color(players[i].color);

        

        for (int j = 0; j < 3; j++) {
            al_draw_filled_rectangle(spot * (1 + 3 * j), spot, spot * (3 + 3 * j), height-spot, al_map_rgb(objectColor[j][0],objectColor[j][1],objectColor[j][2]));
            al_draw_rectangle(spot * (1 + 3 * j), spot, spot * (3 + 3 * j), height - spot, al_map_rgb(objectColor2[j][0], objectColor2[j][1], objectColor2[j][2]), 6);
            
            switch (j) {
            case 0: text = players[i].health; break;
            case 1: text = players[i].bombs.bombAmount; break;
            case 2: text = players[i].bombs.BombPower; break;
            };

            al_draw_textf(font, al_map_rgb(objectColor2[j][0], objectColor2[j][1], objectColor2[j][2]), spot * (1 + 3 * j) + spot , 0.5 * height/2+ al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTER, "%d", text);
        }
        

        al_set_target_bitmap(infoPanel);
        al_draw_bitmap(playerInfo[i], i * TILE * 5, 0.05 * height, 0);
    }

    for (int i = 0; i < playerNumber; i++) {
        al_destroy_bitmap(playerInfo[i]);
    }
    free(playerInfo);
}