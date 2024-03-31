#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "position.h"
#include "bomb.h"

// FUNKCJE BOMBY

int p = 20;

void initBomb(Bomb* bomb, int x, int y, int power) {
    bomb->position.x = x;
    bomb->position.y = y;
    bomb->power = power;
    bomb->bombGraphic = al_create_bitmap(p*2, p*2);
    

    al_set_target_bitmap(bomb->bombGraphic);
    al_draw_filled_circle(p, p, 0, al_map_rgb(255, 40, 40));
    al_draw_circle(p, p, 10, al_map_rgb(255, 255, 255), 2);
    ;
}

               
void addBomb(Bomb** bomb, int x, int y, int power) {
    Bomb* newBomb = malloc(sizeof(Bomb));
    initBomb(newBomb, x, y, power);
    newBomb->next = *bomb;
    *bomb = newBomb;
}



void drawBombs(Bomb* bomb, ALLEGRO_DISPLAY* display) {
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        al_set_target_bitmap(al_get_backbuffer(display));
        al_draw_bitmap(bombElement->bombGraphic, bombElement->position.x-10, bombElement->position.y-10, 0);
    }
}





