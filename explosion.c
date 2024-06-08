#include "explosion.h"
#include <allegro5/allegro.h>
/**
 * @file explosion.c
 * @brief Plik implementujący funkcjonalność bomb i ich efektu.
 */
/**
 * @brief Tworzy nowy wybuch na podanej pozycji.
 *
 * Funkcja alokuje pamięć na nowy wybuch, ustawia jego pozycję i czas trwania,
 * a także tworzy bitmapę grafiki wybuchu.
 *
 * @param explosions Podwójny wskaźnik na początek listy wybuchów.
 * @param x Współrzędna x pozycji wybuchu.
 * @param y Współrzędna y pozycji wybuchu.
 */
void createExplosion(Explosion** explosions, int x, int y) {
    Explosion* newExplosion = malloc(sizeof(Explosion));

    newExplosion->position.x = x;
    newExplosion->position.y = y;
    newExplosion->time = 0.2;

    newExplosion->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newExplosion->graphic);
    al_draw_scaled_bitmap(explosionGraphic, 0, 0, al_get_bitmap_width(explosionGraphic), al_get_bitmap_height(explosionGraphic), 0, 0, TILE, TILE, 0);

    newExplosion->next = *explosions;
    *explosions = newExplosion;
}

/**
 * @brief Rysuje wszystkie wybuchy na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekran gry i rysuje wszystkie wybuchy
 * z listy wybuchów w odpowiednich pozycjach.
 *
 * @param explosions Podwójny wskaźnik na początek listy wybuchów.
 * @param gameDisplay Bitmapa reprezentująca ekran gry.
 */
void drawExplosion(Explosion* explosions, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Explosion* explosion = explosions; explosion != NULL; explosion = explosion->next) {
        al_draw_bitmap(explosion->graphic, explosion->position.x, explosion->position.y, 0);
    }
}

/**
 * @brief Usuwa wybuch z listy wybuchów i zwalnia pamięć.
 *
 * Funkcja usuwa podany wybuch z listy wybuchów, zwalniając pamięć zajętą przez
 * jego bitmapę grafiki oraz samą strukturę wybuchu.
 *
 * @param explosions Podwójny wskaźnik na początek listy wybuchów.
 * @param endExplosion Wskaźnik na wybuch do usunięcia.
 */
void endExplosion(Explosion** explosions, Explosion* endExplosion) {
    if (*explosions == endExplosion) {
        *explosions = endExplosion->next;
    }
    else {
        for (Explosion* explosion = *explosions; explosion != NULL; explosion = explosion->next) {
            if (explosion->next == endExplosion) {
                explosion->next = endExplosion->next;
                break;
            }
        }
    }
    al_destroy_bitmap(endExplosion->graphic);
    free(endExplosion);
}

/**
 * @brief Aktualizuje wybuchy na ekranie i usuwa te, których czas życia minął.
 *
 * Funkcja zmniejsza czas życia każdego wybuchu o odpowiednią wartość na podstawie
 * liczby klatek na sekundę (FPS). Jeśli czas życia wybuchu spadnie poniżej zera,
 * usuwa go z listy wybuchów.
 *
 * @param explosions Podwójny wskaźnik na początek listy wybuchów.
 */
void endExplosions(Explosion** explosions) {
    for (Explosion* explosion = *explosions; explosion != NULL; explosion = explosion->next) {
        explosion->time -= 1.0 / FPS;

        if (explosion->time <= 0) {
            endExplosion(explosions, explosion);
            break;
        }
    }
}

/**
 * @brief Obsługuje logikę wybuchu bomby.
 *
 * Funkcja generuje wybuch bomby na podstawie jej pozycji i mocy, niszcząc bloki
 * oraz raniąc graczy. Wybuch jest generowany w pięciu kierunkach: góra, dół, lewo,
 * prawo oraz środek.
 *
 * @param bomb Wskaźnik na bombę, która wybuchła.
 * @param blocks Podwójny wskaźnik na początek listy bloków na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podwójny wskaźnik na początek listy wybuchów.
 */

void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber, Explosion** explosions) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;

  
    createExplosion(explosions, x, y);


    bool destroyed = false; // Flaga oznaczająca, czy bomba zniszczyła blok
    bool damaged = false;   // Flaga oznaczająca, czy dany gracz został zraniony przez wybuch
    bool explode = false; // Flaga oznaczająca, czy nie ma bloku nie do zniszczniea

    // Środek
    for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
        if (blockElement->position.x == x && blockElement->position.y == y) {
            if (blockElement->health > 0) blockElement->health -= 1;
            
            if (blockElement->health == 1) {            
                al_set_target_bitmap(blockElement->graphic); 
                al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0); 
            };
            if (blockElement->health == 0) breakBlock(blocks, blockElement);
            destroyed = true;
        }
    }

    if (!destroyed) {
        for (int j = 0; j < playerNumber; j++) {
            if (players[j].position.x >= x - TILE / 2 && players[j].position.x <= x + TILE / 2 &&
                players[j].position.y >= y - TILE / 2 && players[j].position.y <= y + TILE / 2) {
                if (!damaged) {
                    if (players[j].health > 0 && players[j].activePower.shieldTime <= 0) {
                        players[j].health -= 1;
                        al_play_sample(hitSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    damaged = true;
                    players[j].activePower.shieldTime = 3.0;
                    break;
                }
            }
        }
    }

    // Prawo
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x + TILE * i;

        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == newX && blockElement->position.y == y) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 1) {
                    al_set_target_bitmap(blockElement->graphic); 
                    al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0); 
                };
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }
        }

        if (!explode) createExplosion(explosions, newX, y);

        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (players[j].position.y >= y - TILE / 3 && players[j].position.y <= y + TILE / 3 &&
                    players[j].position.x >= newX - TILE / 3 && players[j].position.x <= newX + TILE / 3) {
                    if (players[j].health > 0 && players[j].activePower.shieldTime <= 0) {
                        players[j].health -= 1;
                        al_play_sample(hitSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    damaged = true;
                    players[j].activePower.shieldTime = 3.0;
                    break;
                }
            }
        }
    }


    // Lewo
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newX = x - TILE * i;

        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == newX && blockElement->position.y == y) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 1) {
                    al_set_target_bitmap(blockElement->graphic); 
                    al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0); 
                };
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }

        }

        if (!explode) createExplosion(explosions, newX, y);

        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (players[j].position.y >= y - TILE / 3 && players[j].position.y <= y + TILE / 3 &&
                    players[j].position.x >= newX - TILE / 3 && players[j].position.x <= newX + TILE / 3) {
                    if (players[j].health > 0 && players[j].activePower.shieldTime <= 0) {
                        players[j].health -= 1;
                        al_play_sample(hitSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    damaged = true;
                    players[j].activePower.shieldTime = 3.0;
                    break;
                }
            }
        }
    }

    // Góra
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y - TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == newY) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 1) {
                    al_set_target_bitmap(blockElement->graphic); 
                    al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0); 
                };
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }
        }

        if (!explode) createExplosion(explosions, x, newY);

        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (players[j].position.x >= x - TILE / 3 && players[j].position.x <= x + TILE / 3 &&
                    players[j].position.y >= newY - TILE / 3 && players[j].position.y <= newY + TILE / 3) {
                    if (players[j].health > 0 && players[j].activePower.shieldTime <= 0) {
                        players[j].health -= 1;
                        al_play_sample(hitSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    damaged = true;
                    players[j].activePower.shieldTime = 3.0;
                    break;
                }
            }
        }
    }

    // Dół
    destroyed = false;
    damaged = false;
    explode = false;

    for (int i = 1; i <= power && !destroyed; i++) {
        int newY = y + TILE * i;
        for (Block* blockElement = *blocks; blockElement != NULL && !destroyed; blockElement = blockElement->next) {
            if (blockElement->position.x == x && blockElement->position.y == newY) {
                if (blockElement->health == -1) explode = true;
                if (blockElement->health > 0) blockElement->health -= 1;
                if (blockElement->health == 1) {
                    al_set_target_bitmap(blockElement->graphic); 
                    al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0); 
                };
                if (blockElement->health == 0) breakBlock(blocks, blockElement);
                destroyed = true;
            }
        }

        if (!explode) createExplosion(explosions, x, newY);


        if (!destroyed) {
            for (int j = 0; j < playerNumber; j++) {
                if (players[j].position.x >= x - TILE / 3 && players[j].position.x <= x + TILE / 3 &&
                    players[j].position.y >= newY - TILE / 3 && players[j].position.y <= newY + TILE / 3) {
                    if (players[j].health > 0 && players[j].activePower.shieldTime <= 0) {
                        players[j].health -= 1;
                        al_play_sample(hitSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    damaged = true;
                    players[j].activePower.shieldTime = 3.0;
                    break;
                }
            }
        }
    }
}