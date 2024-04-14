#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

#include "player.h"
#include "position.h"
#include "bomb.h"
#include "block.h"
#include "collision.h"
#include "explosion.h"
#include "map.h"
#include "infoPanel.h"


void gameRefresh(ALLEGRO_BITMAP* gameDisplay, Block* blocks, Bomb* bombs, Player* players, int playerNumber, Explosion* explosions) {
	al_set_target_bitmap(gameDisplay);
	al_clear_to_color(al_map_rgb(128, 128, 128));
		
	drawBlocks(blocks, gameDisplay);	
	drawBombs(bombs, gameDisplay);	
	drawPlayer(players, playerNumber, gameDisplay);
	drawExplosion(explosions, gameDisplay);	
}

void displayRefreshing(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* gameDisplay, ALLEGRO_BITMAP* infoPanel ) {
	al_set_target_bitmap(al_get_backbuffer(display));
	
	al_draw_filled_rectangle(0, 0, XSCREEN, al_get_bitmap_height(gameDisplay), al_map_rgb(128, 128, 128));
	al_draw_bitmap(gameDisplay, (XSCREEN-TILE*19)/2, 0, 0);
	al_draw_filled_rectangle(0, al_get_bitmap_height(gameDisplay), XSCREEN, YSCREEN, al_map_rgb(255, 252, 171));
	al_draw_bitmap(infoPanel, (XSCREEN - TILE * 19) / 2, 11 * TILE, 0);

	al_flip_display();
}


// Glowna petla gry
int main() {
	srand(time(0));
	// ZMIENNE ALLEGRO
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	bool run = true;

	// EKRAN
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY* display = NULL;;
	display = al_create_display(XSCREEN, YSCREEN);
	

	// KLAWIATURA
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	ALLEGRO_KEYBOARD_STATE keyState;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	bool key[ALLEGRO_KEY_MAX] = { false };

	// FPS
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	// BITMAP DLA ALL

	ALLEGRO_BITMAP* gameDisplay = al_create_bitmap(XNUMBER*TILE, YNUMBER*TILE);
	ALLEGRO_BITMAP* infoPanel = al_create_bitmap(XNUMBER*TILE,YSCREEN-YNUMBER*TILE);

	// INICJACJA GRY
	

	int playerNumber = 4;
	printf("PLAYER NUMBERS: %d \n", playerNumber);
	Player* players = malloc(playerNumber * sizeof(Player));
	Bomb* bombs = NULL;
	Block* blocks = NULL;
	Explosion* explosions = NULL;

	createMap(&blocks,players, playerNumber);

	// PETLA GRY
	while (run) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);

		if (event.type == ALLEGRO_EVENT_TIMER) {

			movePlayer(players, playerNumber, &keyState, blocks, bombs);
			placeBomb(players, playerNumber, &bombs, &keyState, display);

			timerBomb(&bombs, blocks, players, playerNumber, &explosions);
			endExplosions(&explosions);

			//if (al_key_down(&keyState, ALLEGRO_KEY_E)) players[0].health += 10;
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) run = false;

			gameRefresh(gameDisplay, blocks, bombs, players, playerNumber, explosions);
			drawInfoPanel(infoPanel, players, playerNumber);
			displayRefreshing(display, gameDisplay, infoPanel);
		}
	}

	al_destroy_bitmap(gameDisplay);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	free(players);

	while (blocks != NULL) {
		breakBlock(&blocks, blocks);
	}
	while (bombs != NULL) {
		explodedBomb(&bombs, bombs);
	}
	return 0;
};