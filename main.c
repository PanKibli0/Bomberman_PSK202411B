#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

#include "player.h"
#include "position.h"
#include "bomb.h"

#define FPS 60;
bool run = true;

//DO PRZENIESIENIA
void drawMap(ALLEGRO_BITMAP* map, ALLEGRO_DISPLAY* display) {
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(map, 0, 0, 0);
}


// G³ówna pêtla gry
int main() {
	srand(time(0));
	// ZMIENNE ALLEGRO
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY* display = al_create_display(800, 450);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_KEYBOARD_STATE keyState;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	bool key[ALLEGRO_KEY_MAX] = { false };

	// BITMAP DLA ALL

	ALLEGRO_BITMAP* map = al_create_bitmap(800, 450);
	al_set_target_bitmap(map);
	al_clear_to_color(al_map_rgb(128, 128, 128));

	//ALLEGRO_BITMAP *bombsPlaces = al_create_bitmap(800, 450);



	ALLEGRO_BITMAP* playerGraphic = al_create_bitmap(30, 30);
	al_set_target_bitmap(playerGraphic);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	//al_set_target_bitmap(al_get_backbuffer(display));

	// INICJACJA GRY
		// GRACZ
	int playerNumber = rand() % 3 + 1;
	printf("%d", playerNumber);
	Player* players = malloc(playerNumber * sizeof(Player));

	switch (playerNumber) { // STRZALKI STEROWANIE	
	case 4: initPlayer(&players[3], playerGraphic, rand() % 770, rand() % 420, 3, 20, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_PAD_8, ALLEGRO_KEY_PAD_5, ALLEGRO_KEY_PAD_6, ALLEGRO_KEY_PAD_4, ALLEGRO_KEY_PAD_9});
	case 3: initPlayer(&players[2], playerGraphic, rand() % 770, rand() % 420, 3, 20, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_I, ALLEGRO_KEY_K, ALLEGRO_KEY_L, ALLEGRO_KEY_J, ALLEGRO_KEY_O});
	case 2: initPlayer(&players[1], playerGraphic, rand() % 770, rand() % 420, 3, 20, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_PAD_0});
	case 1: initPlayer(&players[0], playerGraphic, rand() % 770, rand() % 420, 3, 20, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), (int[]) { ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_D, ALLEGRO_KEY_A, ALLEGRO_KEY_E});
	}

		// BOMBY
	Bomb* bomb = NULL;
	


	// PETLA GRY
	while (run) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);

		
		for (int i = 0; i < playerNumber; i++) 
			movePlayer(&players[i], &keyState);
		
		drawMap(map, display);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
				addBomb(&bomb, players[0].position.x, players[0].position.y, 1);
			}
		}

		for (int i = 0; i < playerNumber; i++)
			drawPlayer(&players[i]);

		drawBombs(bomb, display);

		al_flip_display();

	}


	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
};

