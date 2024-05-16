#include <allegro5/allegro_primitives.h>

#include "block.h"
#include "graphics.h"


void addBlock(Block** block, int x, int y, int health) {
	Block* newBlock = malloc(sizeof(Block));

	newBlock->position.x = x;
	newBlock->position.y = y;
	newBlock->health = health;

	newBlock->graphic = al_create_bitmap(TILE, TILE);
	al_set_target_bitmap(newBlock->graphic);
	if (newBlock->health < 0) {
		al_draw_scaled_bitmap(IDblockGraphic, 0, 0, al_get_bitmap_width(IDblockGraphic), al_get_bitmap_height(IDblockGraphic), 0, 0, TILE, TILE, 0);
	}
	else if (newBlock->health == 1) {
		al_draw_scaled_bitmap(DblockGraphic, 0, 0, al_get_bitmap_width(DblockGraphic), al_get_bitmap_height(DblockGraphic), 0, 0, TILE, TILE, 0);
	} 
	else {
		al_draw_scaled_bitmap(hardDblockGraphic, 0, 0, al_get_bitmap_width(hardDblockGraphic), al_get_bitmap_height(hardDblockGraphic), 0, 0, TILE, TILE, 0);
	}

	newBlock->next = *block;
	*block = newBlock;
}

void drawBlocks(Block* block, ALLEGRO_BITMAP* gameDisplay) {
	al_set_target_bitmap(gameDisplay);
	for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
		al_draw_bitmap(blockElement->graphic, blockElement->position.x, blockElement->position.y, 0);
	}
}

void breakBlock(Block** block, Block* breakBlock) {
	if (*block == breakBlock) {
		*block = breakBlock->next;
	}
	else {
		for (Block* blockElement = *block; blockElement != NULL; blockElement = blockElement->next) {
			if (blockElement->next == breakBlock) {
				blockElement->next = breakBlock->next;
			}
		}
	}
	al_destroy_bitmap(breakBlock->graphic);
	free(breakBlock);
}

