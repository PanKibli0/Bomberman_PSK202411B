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
	al_clear_to_color(al_map_rgb(128, 128, 128));
	al_draw_textf(font, al_map_rgb(255, 255, 255), 960, 540, ALLEGRO_ALIGN_CENTER, "%d", choice);
	al_flip_display();
}

void mainMenu(int* playerNumber, int* map, bool* gamework, bool* APPWORK) {
	static int choice = 1;
	bool work = true;

	while (work) {
		drawMainMenu(choice);
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) {
				choice = (choice != 1) ? choice - 1 : 1;
				printf("%d\n", choice);
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) {
				choice = (choice != 3) ? choice + 1 : 3;
				printf("%d\n", choice);
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				switch (choice) {
				case 1: // START
					*playerNumber = 4;
					*map = 12;
					*gamework = true;
					work = false; // Exit the loop
					break;
				case 2: // START
					break;
				case 3: // EXIT
					*APPWORK = false;
					work = false; // Exit the loop
					break;
				}
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
	display = al_create_display(XSCREEN, YSCREEN);

	// KLAWIATURA
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_hide_mouse_cursor(display);
	bool key[ALLEGRO_KEY_MAX] = { false };

	// FPS
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	font = al_load_font("graphics/minecraft.ttf", 40, 0);
	loadGraphics();


	while (APPWORK) {
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);


		
		if (!gamework) mainMenu(&playerNumber, &map, &gamework, &APPWORK); else game(playerNumber, map);
		al_flip_display();
	};

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}