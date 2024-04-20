#include "map.h"
#include "position.h"


void createMap(Block** blocks,Player* players, int playerNumber) {
    //	void initPlayer(Player* player, unsigned int health, int x, int y, float velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);


    //  GRACZE
    switch (playerNumber) { // STRZALKI STEROWANIE	
    case 4: {
        initPlayer(&players[3], 3, (XNUMBER - 2) * TILE, (YNUMBER - 2) * TILE, 2, 3, 3, 2, al_map_rgb(255,255,0), (int[]) { ALLEGRO_KEY_PAD_8, ALLEGRO_KEY_PAD_5, ALLEGRO_KEY_PAD_6, ALLEGRO_KEY_PAD_4, ALLEGRO_KEY_PAD_9 });
        initPlayer(&players[2], 3, (XNUMBER - 2)*TILE, TILE, 3, 3, 3, 2, al_map_rgb(0, 196, 0), (int[]) { ALLEGRO_KEY_I, ALLEGRO_KEY_K, ALLEGRO_KEY_L, ALLEGRO_KEY_J, ALLEGRO_KEY_O });
        initPlayer(&players[1], 3, TILE, (YNUMBER - 2) * TILE, 2, 3, 3, 2, al_map_rgb(0, 0, 255), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_PAD_0 });
        initPlayer(&players[0], 3, TILE, TILE, 2, 3, 3, 2, al_map_rgb(255, 0, 0), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_Q });
        break;
    }
    case 3: {
        initPlayer(&players[2], 3, (XNUMBER - 2) * TILE, TILE, 2, 3, 3, 2, al_map_rgb(0, 196, 0), (int[]) { ALLEGRO_KEY_I, ALLEGRO_KEY_K, ALLEGRO_KEY_L, ALLEGRO_KEY_J, ALLEGRO_KEY_O });
        initPlayer(&players[1], 3, TILE, (YNUMBER - 2) * TILE, 2, 3, 3, 2, al_map_rgb(0, 0, 255), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_PAD_0 });
        initPlayer(&players[0], 3, TILE, TILE, 2, 3, 3, 2, al_map_rgb(255, 0, 0), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_Q });
        break;
    }
    case 2: {
        initPlayer(&players[1], 3, (XNUMBER - 2) * TILE, (YNUMBER - 2) * TILE, 2, 3, 3, 2, al_map_rgb(0, 0, 255), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_PAD_0 });
        initPlayer(&players[0], 3, TILE, TILE, 2, 3, 3, 2, al_map_rgb(255, 0, 0), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_Q });
        break;
    }
    }


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