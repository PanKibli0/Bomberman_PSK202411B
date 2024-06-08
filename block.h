#ifndef BLOCK_H
#define BLOCK_H
/**
 * @file block.h
 * @brief Plik zawieraj¹cy strukturê bloku w grze.
 */
#include <allegro5/allegro.h>
#include "config.h"

/**
 * @brief Struktura reprezentuj¹ca blok w grze.
 *
 * Struktura przechowuje informacje o zdrowiu bloku, jego pozycji, graficznym
 * przedstawieniu oraz wskaŸnik na kolejny blok w liœcie.
 */
typedef struct Block {
    int health;                 /**< Zdrowie bloku */
    Position position;          /**< Pozycja bloku */
    ALLEGRO_BITMAP* graphic;    /**< Graficzne przedstawienie bloku */
    struct Block* next;         /**< WskaŸnik na kolejny blok w liœcie */
} Block;

/**
 * @brief Dodaje nowy blok do listy bloków.
 *
 * Funkcja alokuje pamiêæ dla nowego bloku, ustawia jego pozycjê i zdrowie,
 * tworzy bitmapê bloku i rysuje odpowiedni¹ grafikê w zale¿noœci od zdrowia bloku.
 * Nastêpnie dodaje nowy blok na pocz¹tek listy bloków.
 *
 * @param block Podwójny wskaŸnik na pocz¹tek listy bloków na planszy.
 * @param x Pozycja x nowego bloku.
 * @param y Pozycja y nowego bloku.
 * @param health Zdrowie nowego bloku. Wartoœci mniejsze od 0 oznaczaj¹ blok niezniszczalny.
 */
void addBlock(Block** block, int x, int y, int health);

/**
 * @brief Rysuje wszystkie bloki na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekranie i rysuje wszystkie bloki
 * z listy bloków w odpowiednich pozycjach.
 *
 * @param block WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 */
void drawBlocks(Block* block, ALLEGRO_BITMAP* gameDisplay);

#endif /* BLOCK_H */