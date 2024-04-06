#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "position.h"
#include "bomb.h"


void initBomb(Bomb* bomb, int x, int y, int power, float time, int owner) {
    bomb->position.x = x;
    bomb->position.y = y;
    bomb->power = power;
    bomb->time = time;
    bomb->owner = owner;

    bomb->graphic = al_create_bitmap(40, 40);
    al_set_target_bitmap(bomb->graphic);
    al_draw_rectangle(0, 0, 40, 40, al_map_rgb(255, 255, 255), 40);
    ;
}

bool addBomb(Bomb** bomb, int x, int y, int power, float time, int owner) {
    for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
        int dx = abs(bombElement->position.x - x);
        int dy = abs(bombElement->position.y - y);
        if (dx < 40 && dy < 40) {
            return false;
        }
    }

    Bomb* newBomb = malloc(sizeof(Bomb));
    initBomb(newBomb, x, y, power, time, owner);
    newBomb->next = *bomb;
    *bomb = newBomb;
    return true;
}



void drawBombs(Bomb* bomb, ALLEGRO_DISPLAY* display) {
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
        al_set_target_bitmap(al_get_backbuffer(display));
        al_draw_bitmap(bombElement->graphic, bombElement->position.x, bombElement->position.y, 0);
    }
}

void explodedBomb(Bomb** bomb, Bomb* explodedBomb) {
    if (*bomb == explodedBomb) {
        *bomb = explodedBomb->next;
    }
    else {
        for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
            if (bombElement->next == explodedBomb) {
                bombElement->next = explodedBomb->next;
                break;
            }
        }
    }
    free(explodedBomb);
}

int timerBomb(Bomb** bomb, Block* blocks) {
    for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
        bombElement->time -= 1.0 / FPS;

        if (bombElement->time <= 0) {
            //explosion();
            int owner = bombElement->owner;
            explodedBomb(bomb, bombElement);
            
            return owner +1;
        }
        
    }
    return 0;
}