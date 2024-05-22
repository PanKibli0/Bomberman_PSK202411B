#include "game.h"

extern ALLEGRO_EVENT event;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_KEYBOARD_STATE keyState;
extern ALLEGRO_TIMER* timer;

void gameRefresh(ALLEGRO_BITMAP* gameDisplay, Block* blocks, Bomb* bombs, Player* players, int playerNumber, Explosion* explosions, PowerUp* powerUps) {
	al_set_target_bitmap(gameDisplay);
	al_clear_to_color(al_map_rgb(96, 96, 96));

	drawBlocks(blocks, gameDisplay);
	drawBombs(bombs, gameDisplay);
	drawPlayer(players, playerNumber, gameDisplay);
	drawExplosion(explosions, gameDisplay);
	drawPowerUps(powerUps, gameDisplay);
}

void displayRefreshing(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* gameDisplay, ALLEGRO_BITMAP* infoPanel) {
	al_set_target_bitmap(al_get_backbuffer(display));

	al_draw_filled_rectangle(0, 0, 1920, al_get_bitmap_height(gameDisplay), al_map_rgb(96, 96, 96));
	al_draw_bitmap(gameDisplay, (1920 - TILE * 19) / 2, 0, 0);
	al_draw_filled_rectangle(0, al_get_bitmap_height(gameDisplay), 1920, 1080, al_map_rgb(255, 252, 171));
	al_draw_bitmap(infoPanel, (1920 - TILE * 19) / 2, 11 * TILE, 0);

	al_flip_display();
}


// Glowna petla gry
void game(int playerNumber, int map) {
	bool run = true;
	ALLEGRO_BITMAP* gameDisplay = al_create_bitmap(19 * TILE, 11 * TILE);
	ALLEGRO_BITMAP* infoPanel = al_create_bitmap(19 * TILE, 1080 - 11 * TILE);
	

	// INICJACJA GRY
	Player* players = malloc(playerNumber * sizeof(Player));
	Bomb* bombs = NULL;
	Block* blocks = NULL;
	Explosion* explosions = NULL;
	PowerUp* powerUps = NULL;



	int CHANCE;
	mapLayout(&blocks, players, playerNumber, map, &CHANCE);

	

	// PETLA GRY
	while (run) {
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			if (rand() % CHANCE == 0) {
				createPowerUp(&powerUps, players, playerNumber, blocks, bombs);
			};

			movePlayer(players, playerNumber, &keyState, blocks, bombs);
			placeBomb(players, playerNumber, &bombs, &keyState, display);
			usePower(players, playerNumber, &keyState, blocks, &bombs, powerUps);

			timerBomb(&bombs, blocks, players, playerNumber, &explosions);
			endExplosions(&explosions);

			powerShield(players, playerNumber);
			powerInvisibility(players, playerNumber);
			collectPowerUp(players, playerNumber, &powerUps);
			disappearancePowerUp(&powerUps);

			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) run = false;

			gameRefresh(gameDisplay, blocks, bombs, players, playerNumber, explosions, powerUps);
			drawInfoPanel(infoPanel, players, playerNumber);
			displayRefreshing(display, gameDisplay, infoPanel);

			int alivePlayers = 0;
			for (int i = 0; i < playerNumber; ++i) {
				if (players[i].health > 0) {
					alivePlayers++;
				}
				if (alivePlayers > 2) continue;
			}
			if (alivePlayers == 1) {
				//printf("WYGRANA");
			}

		}
	}


	al_destroy_bitmap(gameDisplay);
	free(players);

	while (blocks != NULL) {
		breakBlock(&blocks, blocks);
	}
	while (bombs != NULL) {
		explodedBomb(&bombs, bombs);
	}

	while (powerUps != NULL) {
		destroyPowerUp(&powerUps, powerUps);
	}
};