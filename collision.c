
#include <math.h>
#include "position.h"
#include "player.h"
#include "bomb.h"
#include "block.h"

bool checkBlockCollision(Player* player, Block* blocks) {
    for (Block* block = blocks; block != NULL; block = block->next) {
        float dx = player->position.x - block->position.x;
        float dy = player->position.y - block->position.y;
        float distance = sqrt(dx * dx + dy * dy);
        if (distance <= 40) {  
            return true; 
        }
    }
    return false; 
}