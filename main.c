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
	al_clear_to_color(al_map_rgb(128, 128, 128));
	al_draw_bitmap(gameDisplay, (1920-TILE*19)/2, 0, 0);
	al_draw_bitmap(infoPanel, 0, 11 * TILE, 0);
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
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY* display = NULL;;
	display = al_create_display(1920, 1080);
	

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
	ALLEGRO_BITMAP* infoPanel = al_create_bitmap(1920,1080-YNUMBER*TILE);

	// INICJACJA GRY
		// GRACZ
	//int playerNumber = rand() % 2 + 2;
	int playerNumber = PLAYERS;
	printf("PLAYER NUMBERS: %d \n", playerNumber);
	Player* players = malloc(playerNumber * sizeof(Player));

	switch (playerNumber) { // STRZALKI STEROWANIE	
		//	void initPlayer(Player* player, unsigned int health, int x, int y, float velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);
	case 4: initPlayer(&players[3], 3, rand() % 770, rand() % 420, 5, 3, 5, 3, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_PAD_8, ALLEGRO_KEY_PAD_5, ALLEGRO_KEY_PAD_6, ALLEGRO_KEY_PAD_4, ALLEGRO_KEY_PAD_9 });
	case 3: initPlayer(&players[2], 3, rand() % 770, rand() % 420, 3, 3, 5, 3, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_I, ALLEGRO_KEY_K, ALLEGRO_KEY_L, ALLEGRO_KEY_J, ALLEGRO_KEY_O });
	case 2: initPlayer(&players[1], 3, TILE, 9*TILE, 2, 3, 5, 3, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_PAD_0 });
	case 1: initPlayer(&players[0], 3, TILE, TILE, 4, 3, 2, 3, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_Q });
	}

	// BOMBY
	Bomb* bombs = NULL;
	Block* blocks = NULL;
	Explosion* explosions = NULL;

	createMap(&blocks);


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

			if (al_key_down(&keyState, ALLEGRO_KEY_E)) players[0].health += 10;
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) run = false;

			gameRefresh(gameDisplay, blocks, bombs, players, playerNumber, explosions);
			drawInfoPanel(infoPanel);
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