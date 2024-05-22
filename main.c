#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <stdio.h>


ALLEGRO_EVENT event;
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* font;


void drawMainMenu(int choice) {
	al_set_target_bitmap(al_get_backbuffer(display));

	const char* options[] = { "START", "INFO", "EXIT" };

	for (int i = 0; i < 3; i++) {
		al_draw_filled_rounded_rectangle(810, 420 + i * 100, 1110, 500 + i * 100 , 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(810, 420 + i * 100, 1110, 500 + i * 100 , 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == i + 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 960, 445 + i * 100 , ALLEGRO_ALIGN_CENTER, options[i]);
	}
	al_flip_display();
}



void ChooseMenu(bool* gamework, bool* work, int* playerNumber, int* map, ALLEGRO_BITMAP* background) {
	int choice = 1;
	*playerNumber = 2;
	*map = 0;
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(background, 0, 0, 0);

	while (1) {
		al_wait_for_event(event_queue, &event);

		// Liczba graczy
		const char* options[] = { "2 Players", "3 Players", "4 Players" };

		al_draw_filled_rounded_rectangle(410, 60, 1510, 140, 45, 45, al_map_rgb(128, 128, 128));
		al_draw_rounded_rectangle(410, 60, 1510, 140, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 650, 85, ALLEGRO_ALIGN_LEFT, "CHOOSE NUMER OF PLAYERS:");

		for (int i = 0; i < 3; i++) {
			ALLEGRO_COLOR textColor = (choice == 1) ? ((i + 2 == *playerNumber) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255)) : ((i + 2 == *playerNumber) ? al_map_rgb(0, 0, 255) : al_map_rgb(255, 255, 255));
			al_draw_filled_rounded_rectangle(410 + i * 400, 150, 710 + i * 400, 230, 45, 45, al_map_rgb(128, 128, 128));
			al_draw_rounded_rectangle(410 + i * 400, 150, 710 + i * 400, 230, 45, 45, al_map_rgb(0, 0, 0), 5);
			al_draw_text(font, textColor, 560 + i * 400, 175, ALLEGRO_ALIGN_CENTER, options[i]);
		}

		// mapa
		al_draw_filled_rounded_rectangle(410, 270, 1510, 350, 45, 45, al_map_rgb(128, 128, 128));
		al_draw_rounded_rectangle(410, 270, 1510, 350, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == 2) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 810, 295, ALLEGRO_ALIGN_LEFT, "CHOOSE A MAP:");
		

		// START
		al_draw_filled_rounded_rectangle(810, 900, 1110, 980, 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(810, 900, 1110, 980, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == 3) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 960, 925, ALLEGRO_ALIGN_CENTER, "PLAY");

		al_flip_display();

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) {
				choice = (choice != 1) ? choice - 1 : 3;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) {
				choice = (choice != 3) ? choice + 1 : 1;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && choice == 1) {
				*playerNumber = (*playerNumber > 2) ? *playerNumber - 1 : 4;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && choice == 1) {
				*playerNumber = (*playerNumber < 4) ? *playerNumber + 1 : 2;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				switch (choice) {
				case 1:
					// Wybór liczby graczy
					break;
				case 2:
					// Wybór mapy
					break;
				case 3:
					*map = rand() % 12 + 1;
					*gamework = true;
					*work = false;
					return;
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				al_draw_bitmap(background, 0, 0, 0);
				return;
			}
		}
	}
	al_destroy_bitmap(background);
}

void mainMenu(int* playerNumber, int* map, bool* gamework, bool* APPWORK) {
	static int choice = 1;
	bool work = true;

	ALLEGRO_BITMAP* background = al_load_bitmap("graphics/background.png");
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(background, 0, 0, 0);


	while (work) {
		drawMainMenu(choice);
		al_wait_for_event(event_queue, &event);
		al_flip_display();
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) {
				choice = (choice != 1) ? choice - 1 : 1;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) {
				choice = (choice != 3) ? choice + 1 : 3;
			}
			
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				switch (choice) {
				case 1: // START
					ChooseMenu(gamework, &work, playerNumber, map, background);
					break;
				case 2: // INFO
					//InfoMenu();
					*map = rand() % 12 + 1;
					*playerNumber = rand()%2+2;
					work = false;
					*gamework = true;
					break;
				case 3: // EXIT
					*APPWORK = false;
					work = false;
					break;
				}

				choice = 1;
			}
		}
	}
}


int main() {
	int playerNumber = 0, map = 0;
	bool gamework = false;

	srand(time(0));
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	bool APPWORK = true;

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(1920, 1080);

	// KLAWIATURA
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_hide_mouse_cursor(display);
	bool key[ALLEGRO_KEY_MAX] = { false };

	// FPS
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	font = al_load_font("graphics/font.ttf", 40, 0);


	while (APPWORK) {
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);

		if (!gamework) { mainMenu(&playerNumber, &map, &gamework, &APPWORK); }
		else {
			loadGraphics();
			game(playerNumber, map);
		}
	};


	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}