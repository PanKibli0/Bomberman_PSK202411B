#include <allegro5/allegro_primitives.h>
/**
 * @file block.c
 * @brief Plik implementacji blok�w i ich funkcjonalno�ci.
 */
#include "block.h"
#include "graphics.h"

 /**
 * @brief Dodaje nowy blok do listy blok�w.
 *
 * Funkcja alokuje pami�� dla nowego bloku, ustawia jego pozycj� i zdrowie,
 * tworzy bitmap� bloku i rysuje odpowiedni� grafik� w zale�no�ci od zdrowia bloku.
 * Nast�pnie dodaje nowy blok na pocz�tek listy blok�w.
 *
 * @param block Podw�jny wska�nik na pocz�tek listy blok�w na planszy.
 * @param x Pozycja x nowego bloku.
 * @param y Pozycja y nowego bloku.
 * @param health Zdrowie nowego bloku. Warto�ci mniejsze od 0 oznaczaj� blok niezniszczalny.
 */
void addBlock(Block** block, int x, int y, int health) {
    Block* newBlock = malloc(sizeof(Block));

    newBlock->position.x = x;
    newBlock->position.y = y;
    newBlock->health = health;

    newBlock->graphic = al_create_bitmap(TILE, TILE);
    al_set_target_bitmap(newBlock->graphic);
    if (newBlock->health < 0) {
        al_draw_scaled_bitmap(IDblockGraphic, 0, 0, al_get_bitmap_width(IDblockGraphic), al_get_bitmap_height(IDblockGraphic), 0, 0, TILE, TILE, 0);
    }
    else if (newBlock->health == 1) {
        al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0);
    }
    else {
        al_draw_scaled_bitmap(hardDblockGraphic, 0, 0, al_get_bitmap_width(hardDblockGraphic), al_get_bitmap_height(hardDblockGraphic), 0, 0, TILE, TILE, 0);
    }

    newBlock->next = *block;
    *block = newBlock;
}

/**
 * @brief Rysuje wszystkie bloki na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekranie i rysuje wszystkie bloki
 * z listy blok�w w odpowiednich pozycjach.
 *
 * @param block Wska�nik na pocz�tek listy blok�w na planszy.
 * @param gameDisplay Bitmapa reprezentuj�ca ekran gry.
 */
void drawBlocks(Block* block, ALLEGRO_BITMAP* gameDisplay) {
    al_set_target_bitmap(gameDisplay);
    for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
        al_draw_bitmap(blockElement->graphic, blockElement->position.x, blockElement->position.y, 0);
    }
}

/**
 * @brief Usuwa blok z listy blok�w i zwalnia zaj�t� przez niego pami��.
 *
 * Funkcja usuwa wskazany blok z listy blok�w, niszczy jego bitmap�
 * i zwalnia zaj�t� przez niego pami��.
 *
 * @param block Podw�jny wska�nik na pocz�tek listy blok�w na planszy.
 * @param breakBlock Wska�nik na blok do usuni�cia.
 */
void breakBlock(Block** block, Block* breakBlock) {
    if (*block == breakBlock) {
        *block = breakBlock->next;
    }
    else {
        for (Block* blockElement = *block; blockElement != NULL; blockElement = blockElement->next) {
            if (blockElement->next == breakBlock) {
                blockElement->next = breakBlock->next;
            }
        }
    }
    al_destroy_bitmap(breakBlock->graphic);
    free(breakBlock);
}