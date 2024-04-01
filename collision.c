
#include "position.h"
#include "player.h"
#include "bomb.h"
#include "block.h"

/*
bool checkBombCollision(Player* player, Bomb* bombs) {
    for (Bomb* bomb = bombs; bomb != NULL; bomb = bomb->next) {
        float dx = player->position.x - bomb->position.x;
        float dy = player->position.y - bomb->position.y;
        float distance = sqrt(dx * dx + dy * dy);
        if (distance <= 40) { 
            return true; 
        }
    }
    return false; 
}
*/