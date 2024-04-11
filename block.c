#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


#include "block.h"


void initBlock(Block* block, int x, int y, int health) {
	block->position.x = x;
	block->position.y = y;
	block->health = health;

	block->graphic = al_create_bitmap(TILE, TILE);
	al_set_target_bitmap(block->graphic);
	if (block->health < 0) {
		al_draw_filled_rectangle(0, 0, TILE, TILE, al_map_rgb(196, 196, 196));
		al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(64, 64, 64), 10);
	}
	else {
		al_draw_filled_rectangle(0, 0, TILE, TILE, al_map_rgb(192, 128, 0));
		al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(192, 64, 0), 10);
		al_draw_line(0, 0, TILE, TILE, al_map_rgb(192, 64, 0), 5);
	};
}

bool addBlock(Block** block, int x, int y, int health) {
	for (Block* blockElement = *block; blockElement != NULL; blockElement = blockElement->next) {
		int dx = abs(blockElement->position.x - x);
		int dy = abs(blockElement->position.y - y);
		if (dx < TILE && dy < TILE) {
			return false;
		}
	}

	Block* newBlock = malloc(sizeof(Block));
	initBlock(newBlock, x, y, health);
	newBlock->next = *block;
	*block = newBlock;
	return true;
}

void drawBlocks(Block* block, ALLEGRO_DISPLAY* display) {
	for (Block* blockElement = block; blockElement != NULL; blockElement = blockElement->next) {
		al_set_target_bitmap(al_get_backbuffer(display));
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

