#include "explode.h"
#include "bomb.h"
#include "block.h"
#include "player.h"

#include <allegro5/allegro_primitives.h>

/*
void explode(Bomb* bomb, Block** blocks, Player* players, int playerCount) {
    int bombX = (int)(bomb->position.x + 20) / 40; 
    int bombY = (int)(bomb->position.y + 20) / 40; 

    // Zniszcz bloki w otoczeniu bomby
    for (int i = bombX - bomb->power; i <= bombX + bomb->power; ++i) {
        for (int j = bombY - bomb->power; j <= bombY + bomb->power; ++j) {
            if (i >= 0 && i < 960 && j >= 0 && j < 540) {
                if (abs(i - bombX) + abs(j - bombY) <= bomb->power) { 
                    destroyBlock(blocks, i, j);
                }
            }
        }
    }

    // Zadaj obra¿enia graczom znajduj¹cym siê w zasiêgu wybuchu
    for (int i = 0; i < playerCount; ++i) {
        float distanceX = players[i].position.x - bomb->position.x;
        float distanceY = players[i].position.y - bomb->position.y;
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        if (distance <= bomb->power * 40) { 
            players[i].health -= 1; 
        }
    }
}
*/