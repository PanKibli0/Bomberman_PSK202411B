#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

#include "player.h"
#include "position.h"
#include "bomb.h"
#include "block.h"

bool run = true;

void drawMap(ALLEGRO_BITMAP* map, ALLEGRO_DISPLAY* display) {
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(map, 0, 0, 0);
};

void displayRefreshing(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* map,Block* blocks, Bomb* bombs, Player* players, int playerNumber) {
	drawMap(map, display);
	drawBlocks(blocks, display);
	drawBombs(bombs, display);
	for (int i = 0; i < playerNumber; i++)
		drawPlayer(&players[i], display);
	al_flip_display();

};

// USUNAC DO CZEGOS INNEGO POTRZEBNE
void Blocks(Block** blocks) {
	for (int i = 0; i < rand() % 10+10; i++) {
		addBlock(blocks, rand() % 920, rand() % 500, 1);
	}
}
// /\ USUNAC

// G��wna p�tla gry
int main() {
	srand(time(0));
	// ZMIENNE ALLEGRO
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY* display = al_create_display(960, 540);

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	// KLAWIATURA
	ALLEGRO_KEYBOARD_STATE keyState;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	bool key[ALLEGRO_KEY_MAX] = { false };

	// FPS
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	
	// BITMAP DLA ALL

	ALLEGRO_BITMAP* map = al_create_bitmap(960, 540);
	al_set_target_bitmap(map);
	al_clear_to_color(al_map_rgb(128, 128, 128));

	// INICJACJA GRY
		// GRACZ
	int playerNumber = rand() % 3 + 1;
	printf("PLAYER NUMBERS: %d \n", playerNumber);
	Player* players = malloc(playerNumber * sizeof(Player));

	switch (playerNumber) { // STRZALKI STEROWANIE	
	//	void initPlayer(Player * player, unsigned int health, int x, int y, float velocity, int bombAmount, float bombTime, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);
	case 4: initPlayer(&players[3], 3,rand() % 770, rand() % 420, (float) 5, 3, 5, 1, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_PAD_8, ALLEGRO_KEY_PAD_5, ALLEGRO_KEY_PAD_6, ALLEGRO_KEY_PAD_4, ALLEGRO_KEY_PAD_9});
	case 3: initPlayer(&players[2], 3,rand() % 770, rand() % 420, (float) 3, 3, 5, 1, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_I, ALLEGRO_KEY_K, ALLEGRO_KEY_L, ALLEGRO_KEY_J, ALLEGRO_KEY_O});
	case 2: initPlayer(&players[1], 3,rand() % 770, rand() % 420, (float) 2 , 3, 1, 1, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_PAD_0});
	case 1: initPlayer(&players[0], 3,rand() % 770, rand() % 420, (float) 2 , 30, 2.5, 1, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_Q});
	}

		// BOMBY
	Bomb* bombs = NULL;
	
		// BLOKI
	Block* blocks = NULL;

	Blocks(&blocks);

	// PETLA GRY
	while (run) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			

			for (int i = 0; i < playerNumber; i++)
				movePlayer(&players[i], &keyState, blocks, bombs);

			for (int i = 0; i < playerNumber; i++)
				placeBomb(&players[i], &bombs, &keyState);

			timerBomb(&bombs);

			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) run = false;

			displayRefreshing(display, map, blocks, bombs, players, playerNumber);
		}
	}

	al_destroy_bitmap(map);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
};

