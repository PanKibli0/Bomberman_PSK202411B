#ifndef BLOCK_H
#define BLOCK_H
/**
 * @file block.h
 * @brief Plik zawieraj�cy struktur� bloku w grze.
 */
#include <allegro5/allegro.h>
#include "config.h"

/**
 * @brief Struktura reprezentuj�ca blok w grze.
 *
 * Struktura przechowuje informacje o zdrowiu bloku, jego pozycji, graficznym
 * przedstawieniu oraz wska�nik na kolejny blok w li�cie.
 */
typedef struct Block {
    int health;                 /**< Zdrowie bloku */
    Position position;          /**< Pozycja bloku */
    ALLEGRO_BITMAP* graphic;    /**< Graficzne przedstawienie bloku */
    struct Block* next;         /**< Wska�nik na kolejny blok w li�cie */
} Block;

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
void addBlock(Block** block, int x, int y, int health);

/**
 * @brief Rysuje wszystkie bloki na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekranie i rysuje wszystkie bloki
 * z listy blok�w w odpowiednich pozycjach.
 *
 * @param block Wska�nik na pocz�tek listy blok�w na planszy.
 * @param gameDisplay Bitmapa reprezentuj�ca ekran gry.
 */
void drawBlocks(Block* block, ALLEGRO_BITMAP* gameDisplay);

#endif /* BLOCK_H */