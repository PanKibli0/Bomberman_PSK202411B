#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


#include "block.h"

void addBlock(Block** block, int x, int y, int health) {
	Block* newBlock = malloc(sizeof(Block));

	newBlock->position.x = x;
	newBlock->position.y = y;
	newBlock->health = health;

	newBlock->graphic = al_create_bitmap(TILE, TILE);
	al_set_target_bitmap(newBlock->graphic);
	if (newBlock->health < 0) {
		al_draw_filled_rectangle(0, 0, TILE, TILE, al_map_rgb(196, 196, 196));
		al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(64, 64, 64), 10);
	}
	else {
		al_draw_filled_rectangle(0, 0, TILE, TILE, al_map_rgb(192, 128, 0));
		al_draw_rectangle(0, 0, TILE, TILE, al_map_rgb(192, 64, 0), 10);
		al_draw_line(0, 0, TILE, TILE, al_map_rgb(192, 64, 0), 5);
	};

	newBlock->next = *block;
	*block = newBlock;
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

