#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "position.h"
#include "bomb.h"
#include "explosion.h"
#include "player.h"
#include "graphics.h"


bool addBomb(Bomb** bomb, int x, int y, int power, float time, Player* owner) {
    for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
        int dx = abs(bombElement->position.x - x);
        int dy = abs(bombElement->position.y - y);
        if (dx < TILE && dy < TILE) {
            return false;
        }
    }

    Bomb* newBomb = malloc(sizeof(Bomb));
    
    newBomb->position.x = x;
    newBomb->position.y = y;
    newBomb->power = power;
    newBomb->time = time;
    newBomb->owner = owner;

    newBomb->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newBomb->graphic);
    al_draw_scaled_bitmap(bombGraphic, 0, 0, al_get_bitmap_width(bombGraphic), al_get_bitmap_height(bombGraphic), 0,0, TILE, TILE, 0);

    printf("RYSUJE ALE COS ZJEBALEM\n");

    newBomb->next = *bomb;
    *bomb = newBomb;

    return true;
}



void drawBombs(Bomb* bomb, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Bomb* bombElement = bomb; bombElement != NULL; bombElement = bombElement->next) {
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

void timerBomb(Bomb** bomb, Block* blocks, Player* players, int playerNumber, Explosion** explosions) {
    for (Bomb* bombElement = *bomb; bombElement != NULL; bombElement = bombElement->next) {
        bombElement->time -= 1.0 / FPS;

        if (bombElement->time <= 0) {
            
            explosion(bombElement, &blocks, players, playerNumber, explosions);
            bombElement->owner->bombs.bombAmount++;
            al_destroy_bitmap(bombElement->graphic);
            explodedBomb(bomb, bombElement);
            break;
        }    
    }
}