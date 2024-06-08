#include "map.h"
#include "config.h"

void createBorder(Block** blocks) {
    // lewo prawo
    for (int i = 0; i < 19; i++) {
        addBlock(blocks, i * TILE, 0, -1);
        addBlock(blocks, i * TILE, 10 * TILE, -1);
    }

    // gora dol
    for (int i = 0; i < 11; i++) {
        addBlock(blocks, 0, i * TILE, -1);
        addBlock(blocks, 18 * TILE, i * TILE, -1);
    }
}

void createMap(Block** blocks, int map[9][17], Player* players, int playerNumber) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            if (map[i][j] != 0) {
                switch (map[i][j]) {
                    // void initPlayer(Player* player, unsigned int health, int x, int y, float velocity, int bombAmount, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);

                case 10: // Player 1
                    if (playerNumber >= 1) {
                        initPlayer(players, 0, 3, (j + 1) * TILE, (i + 1) * TILE, 2, 1, 1, al_map_rgb(106,55,113), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_E, ALLEGRO_KEY_R });
                    }
                    break;
                case 20: // Player 2
                    if (playerNumber >= 2) {
                        initPlayer(players,1, 3, (j + 1) * TILE, (i + 1) * TILE, 2, 1, 1, al_map_rgb(237, 28, 36), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RSHIFT, ALLEGRO_KEY_RCTRL });
                    }
                    break;
                case 30: // Player 3
                    if (playerNumber >= 3) {
                        initPlayer(players,2, 3, (j + 1) * TILE, (i + 1) * TILE, 2, 1, 1, al_map_rgb(0, 73, 232), (int[]) { ALLEGRO_KEY_I, ALLEGRO_KEY_K, ALLEGRO_KEY_L, ALLEGRO_KEY_J, ALLEGRO_KEY_O, ALLEGRO_KEY_P });
                    }
                    break;
                case 40: // Player 4
                    if (playerNumber >= 4) {
                        initPlayer(players,3 ,3, (j + 1) * TILE, (i + 1) * TILE, 2, 1, 1, al_map_rgb(1, 194, 0), (int[]) { ALLEGRO_KEY_PAD_8, ALLEGRO_KEY_PAD_5, ALLEGRO_KEY_PAD_6, ALLEGRO_KEY_PAD_4, ALLEGRO_KEY_PAD_SLASH, ALLEGRO_KEY_PAD_ASTERISK });
                    }
                    else if (playerNumber == 2) {
                        initPlayer(players,1, 3, (j + 1) * TILE, (i + 1) * TILE, 2, 1, 1, al_map_rgb(237, 28, 36), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RSHIFT, ALLEGRO_KEY_RCTRL });
                    }
                    break;
                default:
                    if (map[i][j] == -1) { addBlock(blocks, (j + 1) * TILE, (i + 1) * TILE, map[i][j]); }
                    else if (rand() % 10 == 0) { addBlock(blocks, (j + 1) * TILE, (i + 1) * TILE, 2); }
                    else if (rand() % 20 == 0) break;
                    else { addBlock(blocks, (j + 1) * TILE, (i + 1) * TILE, map[i][j]); };
                    break;
                }
            }
        }
    }
    createBorder(blocks);
}



void mapLayout(Block** blocks, Player* players, int playerNumber, int mapIndex, int* CHANCE) {

    switch (mapIndex) {
    case 1: {
        int map[9][17] = {
            {10, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 30},
            {0, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 0},
            {20, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 40}
        };
        *CHANCE = 100;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 2: {
        int map[9][17] = {
            {10, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 30},
            {0, -1, -1, -1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, -1, -1, 0},
            {1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1},
            {1, -1, 1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, 1, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, 1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, 1, -1, 1},
            {1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1},
            {0, -1, -1, -1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, -1, -1, 0},
            {20, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 40}
        };
        *CHANCE = 100;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 3: {
        int map[9][17] = {
            {10, 0, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 0, 30},
            {0, -1, 1, -1, 1, -1, 1, 1, -1, 1, 1, -1, 1, -1, 1, -1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {-1, -1, 1, -1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, 1, -1, -1},
            {1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1},
            {-1, -1, 1, -1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, 1, -1, -1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, -1, 1, -1, 1, -1, 1, 1, -1, 1, 1, -1, 1, -1, 1, -1, 0},
            {20, 0, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 0, 40}
        };
        *CHANCE = 100;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 4: {
        int map[9][17] = {
            {10, 0, -1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 0, 30},
            {0, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 0},
            {-1, 1, 1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, 1, 1, -1},
            {1, -1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, -1, 1},
            {-1, 1, 1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, 1, 1, -1},
            {0, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 0},
            {20, 0, -1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 0, 40}
        };
        *CHANCE = 150;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 5: {
        int map[9][17] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, 0, -1, 1, -1, 1, 1, -1, 1, 1, -1, 1, -1, 0, -1, 1},
            {1, 0, 10, -1, 1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 30, 0, 1},
            {1, -1, -1, -1, 1, 1, 1, -1, 1, -1, 1, 1, 1, -1, -1, -1, 1},
            {1, 1, 1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, 1},
            {1, -1, -1, -1, 1, 1, 1, -1, 1, -1, 1, 1, 1, -1, -1, -1, 1},
            {1, 0, 20, -1, 1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 40, 0, 1},
            {1, -1, 0, -1, 1, -1, 1, 1, -1, 1, 1, -1, 1, -1, 0, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };
        *CHANCE = 80;
        createMap(blocks, map, players, playerNumber);
        break;
    }
    case 6: {
        int map[9][17] = {
            {1, 1, 1, -1, -1, 0, 1, 1, -1, 1, 1, 0, -1, -1, 1, 1, 1},
            {1, -1, 1, 1, 0, 10, -1, 1, -1, 1, -1, 30, 0, 1, 1, -1, 1},
            {1, -1, -1, 1, 1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {-1, -1, -1, -1, -1, -1, -1, 1, -1, 1, -1, -1, -1, -1, -1, -1, -1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, -1, 1, 1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, -1, 1},
            {1, -1, 1, 1, 0, 20, -1, 1, -1, 1, -1, 40, 0, 1, 1, -1, 1},
            {1, 1, 1, -1, -1, 0, 1, 1, -1, 1, 1, 0, -1, -1, 1, 1, 1}
        };
        *CHANCE = 75;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 7: {
        int map[9][17] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, 1},
            {1, 0, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 30, 0, 1},
            {1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, 1},
            {1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1},
            {1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, 1},
            {1, 0, 20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 40, 0, 1},
            {1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };
        *CHANCE = 120;
        createMap(blocks, map, players, playerNumber);
        break;
    }
    case 8: {
        int map[9][17] = {
           {-1, 1, 1, -1, 1, -1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 0, 10, 0, 1, -1, 1, 1, 1, 1, -1, 1, -1, 0, 30, 0, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, -1, 1, 1, 1, 1, 1, -1, -1, 1, -1, 1, 1, 1, 1, -1, 1},
            {1, 1, -1, 1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 0, 1, 1},
            {1, 0, 20, 0, 1, 1, 1, 1, -1, 1, 1, 1, -1, 0, 40, 0, 1},
            {1, 1, 0, 1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, 0, 1, -1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, -1, 1, 1}
        };
        *CHANCE = 120;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 9: {
        int map[9][17] = {
            {10, 0, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 0, 30},
            {0, 0, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 0, 0},
            {-1, 1, -1, 1, 1, 1, 1, -1, 1, -1, 1, 1, 1, 1, -1, 1, -1},
            {1, 1, 1, 1, 1, 1, -1, -1, 0, -1, -1, 1, 1, 1, 1, 1, 1},
            {1, 1, -1, 1, -1, 1, 1, 0, 0, 0, 1, 1, -1, 1, -1, 1, 1},
            {1, 1, 1, 1, 1, 1, -1, -1, 0, -1, -1, 1, 1, 1, 1, 1, 1},
            {-1, 1, -1, 1, 1, 1, 1, -1, 1, -1, 1, 1, 1, 1, -1, 1, -1},
            {0, 0, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 0, 0},
            {20, 0, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 0, 40}
        };
        *CHANCE = 60;
        createMap(blocks, map, players, playerNumber);
        break;
    }
    case 10: {
        int map[9][17] = {
            {-1, 1, 1, -1, 1, 1, -1, 1, -1, 1, -1, 1, 1, -1, 1, 1, -1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 0, -1, 1, 1, -1, 1, -1, 1, -1, 1, -1, 1, 1, -1, 0, 0},
            {10, -1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, -1, 30},
            {-1, 1, 1, 1, 1, -1, 1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1},
            {20, -1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, -1, 40},
            {0, 0, -1, 1, 1, -1, 1, -1, 1, -1, 1, -1, 1, 1, -1, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {-1, 1, 1, -1, 1, 1, -1, 1, -1, 1, -1, 1, 1, -1, 1, 1, -1}
        };
        *CHANCE = 80;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    case 11: {
        int map[9][17] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 10, -1, 30, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 20, -1, 40, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
        *CHANCE = 500;
        createMap(blocks, map, players, playerNumber);
        break;
    }
    case 12: {
        int map[9][17] = {
            {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40}
        };
        *CHANCE = 500;
        createMap(blocks, map, players, playerNumber);
        break;
    };
    }
}
