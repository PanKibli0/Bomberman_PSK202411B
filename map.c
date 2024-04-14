#include "map.h"

void createMap(Block** blocks) {
    
	// lewo prawo
	for (int i = 0; i < TILE * 19; i += TILE) {
		addBlock(blocks, i , 0, -1);
		addBlock(blocks, i, TILE * 10, -1);
	}

	// gora dol
	for (int i = TILE; i < TILE * 10; i += TILE) {
		addBlock(blocks, 0 , i, -1);
		addBlock(blocks, TILE * 18 , i, -1);
	}

    
	// siatka
	for (int i = TILE * 2; i < TILE * 19; i += TILE * 2) {
		for (int j = TILE * 2; j < TILE * 10; j += TILE * 2) {
			addBlock(blocks, i , j, -1);
		};
	};
    

	
    // niszcznie
    for (int i = TILE; i < TILE * 18; i += TILE) {
        for (int j = TILE; j < TILE * 10; j += TILE) {
            // Sprawdzenie, czy aktualna pozycja nie jest w rogach ani ich bezpoœrednim s¹siedztwie
            if (!((i == TILE && j == TILE) || (i == TILE && j == TILE * 2) || (i == TILE*2 && j==TILE) || // LEWY GORNY ROG
                (i == TILE*17 && j == TILE) || (i == TILE * 16 && j == TILE) || (i == TILE * 17 && j == TILE*2) || // PRAWY GORNY ROG
                (i == TILE && j == TILE * 9) || (i == TILE && j == TILE * 8) || (i == TILE*2 && j == TILE * 9) || // LEWY DOLNY ROG
                (i == TILE * 17 && j == TILE*9) || (i == TILE * 16 && j == TILE*9) || (i == TILE * 17 && j == TILE * 8) // PRAWY DOLNY ROG
                ))
            {
                // Sprawdzenie, czy na danej pozycji nie ma ju¿ bloku
                bool empty = true;
                for (Block* blockElement = *blocks; blockElement != NULL; blockElement = blockElement->next) {
                    if (blockElement->position.x == i  && blockElement->position.y == j) {
                        empty = false;
                        break;
                    }
                }
                // Dodanie bloku tylko jeœli pozycja jest wolna
                if (empty) {
                    addBlock(blocks, i , j, 1);
                }
            }
        }
    }
}