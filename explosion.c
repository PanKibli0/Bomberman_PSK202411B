#include "explosion.h"
#include "bomb.h"
#include "block.h"
#include "player.h"
#include "collision.h"


void explosion(Bomb* bomb, Block** blocks, Player* players, int playerNumber) {
    int power = bomb->power;

    for (int i = 1; i <= power; ++i) {
        float x = bomb->position.x + 40 * i;
        float y = bomb->position.y;
        if (checkBlockCollision(x, y, blocks)) {
            printf("EXPLODE RIGHT");
            break;
        }
    }

    

}
