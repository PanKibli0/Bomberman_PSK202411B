#include "explosion.h"
#include "bomb.h"
#include "block.h"
#include "player.h"
#include "collision.h"

#include <allegro5/allegro_primitives.h>

void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber) {
    int x = bomb->position.x;
    int y = bomb->position.y;
    int power = bomb->power;
    
    printf("\t explosion: %d %d \n", x, y);

    //for (!checkBlock);
}