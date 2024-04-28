#include <allegro5/allegro_primitives.h>
#include "powerup.h"
#include "graphics.h"

/*
void createPowerUp(PowerUp** powerUps, int x, int y, PowerUpType type) {
    PowerUp* newPowerUp = malloc(sizeof(PowerUp));

    newPowerUp->type = type;
    newPowerUp->position.x = x;
    newPowerUp->position.y = y;

    // Grafika dla power-upów
    newPowerUp->graphic = al_create_bitmap(TILE/2, TILE/2);
    al_set_target_bitmap(newPowerUp->graphic);
    al_clear_to_color(al_map_rgb(255, 255, 255)); // Bia³y kwadrat - placeholder
    al_draw_rectangle(0, 0, TILE/2, TILE/2, al_map_rgb(0, 0, 0), 1); // Ramka

    newPowerUp->next = *powerUps;
    *powerUps = newPowerUp;
}

void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (PowerUp* powerUp = powerUps; powerUp != NULL; powerUp = powerUp->next) {
        al_draw_bitmap(powerUp->graphic, powerUp->position.x, powerUp->position.y, 0);
    }
}

void collectPowerUp(Player* player, PowerUp** powerUps) {
    for (PowerUp* powerUp = *powerUps; powerUp != NULL; powerUp = powerUp->next) {
        if (player->position.x < powerUp->position.x + TILE/2 &&
            player->position.x + TILE > powerUp->position.x &&
            player->position.y < powerUp->position.y + TILE/2 &&
            player->position.y + TILE > powerUp->position.y) {
            // Kolekcja power-upu
            switch (powerUp->type) {
            case HEALTH:
                player->health++;
                break;
            case BOMB_POWER:
                player->bombs.BombPower++;
                break;
            }
            // Usuniêcie power-upu z listy
            destroyPowerUp(powerUps, powerUp);
            break;
        }
    }
}



void destroyPowerUp(PowerUp** powerUps, PowerUp* powerUp) {
    if (*powerUps == powerUp) {
        *powerUps = powerUp->next;
    }
    else {
        for (PowerUp* powerupElement = *powerUps; powerupElement != NULL; powerupElement = powerupElement->next) {
            if (powerupElement->next == powerUp) {
                powerupElement->next = powerUp->next;
                break;
            }
        }
    }
    al_destroy_bitmap(powerUp->graphic);
    free(powerUp);
}
*/
