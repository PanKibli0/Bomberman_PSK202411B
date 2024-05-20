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

	const char* options[] = { "START", "INFO", "EXIT" };

	for (int i = 0; i < 3; i++) {
		al_draw_filled_rectangle((XSCREEN - 300) / 2, (YSCREEN - 3 * 80) / 2 + i * (80 + 20), (XSCREEN + 300) / 2, (YSCREEN - 3 * 80) / 2 + i * (80 + 20) + 80, al_map_rgb(192, 192, 192));
		al_draw_rectangle((XSCREEN - 300) / 2, (YSCREEN - 3 * 80) / 2 + i * (80 + 20), (XSCREEN + 300) / 2, (YSCREEN - 3 * 80) / 2 + i * (80 + 20) + 80, al_map_rgb(0, 0, 0), 3);

		al_draw_text(font, (choice == i + 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255),
			XSCREEN / 2, (YSCREEN - 3 * 80) / 2 + i * (80 + 20) + (80 - al_get_font_line_height(font)) / 2 + 5, ALLEGRO_ALIGN_CENTER, options[i]);
	}
	al_flip_display();
}



void drawChoiceMenu(bool* gamework, bool* work, int* playerNumber, int* map) {
	int choice = 1;
	int playRectWidth = 100; // Szerokość prostokąta dla opcji "PLAY"
	int playRectHeight = 40; // Wysokość prostokąta dla opcji "PLAY"

	while (1) {
		al_wait_for_event(event_queue, &event);
		al_clear_to_color(al_map_rgb(128, 128, 128)); // Szare tło

		al_draw_filled_rounded_rectangle(XSCREEN / 4, YSCREEN / 4 - 50, XSCREEN * 3 / 4, YSCREEN / 4, 5, 5, al_map_rgb(255, 255, 255)); // Biały prostokąt dla opcji 1 z zaokrąglonymi rogami
		al_draw_rounded_rectangle(XSCREEN / 4, YSCREEN / 4 - 50, XSCREEN * 3 / 4, YSCREEN / 4, 5, 5, al_map_rgb(0, 0, 0), 2); // Czarna obwódka dla opcji 1 z zaokrąglonymi rogami
		al_draw_text(font, (choice == 1) ? al_map_rgb(0, 0, 0) : al_map_rgb(100, 100, 100), XSCREEN / 2, YSCREEN / 4 - 70, ALLEGRO_ALIGN_CENTER, "Choose number of players:"); // Czarny tekst dla opcji 1, szary dla pozostałych

		// Rysowanie drugiego prostokąta i tekstu dla opcji 2
		al_draw_filled_rounded_rectangle(XSCREEN / 4, YSCREEN / 4, XSCREEN * 3 / 4, YSCREEN / 4 + 50, 5, 5, al_map_rgb(255, 255, 255)); // Biały prostokąt dla opcji 2 z zaokrąglonymi rogami
		al_draw_rounded_rectangle(XSCREEN / 4, YSCREEN / 4, XSCREEN * 3 / 4, YSCREEN / 4 + 50, 5, 5, al_map_rgb(0, 0, 0), 2); // Czarna obwódka dla opcji 2 z zaokrąglonymi rogami
		al_draw_text(font, (choice == 2) ? al_map_rgb(0, 0, 0) : al_map_rgb(100, 100, 100), XSCREEN / 2, YSCREEN / 4 - 20, ALLEGRO_ALIGN_CENTER, "Choose a map:"); // Czarny tekst dla opcji 2, szary dla pozostałych

		// Rysowanie trzeciego prostokąta i tekstu dla opcji "PLAY"
		al_draw_filled_rounded_rectangle(XSCREEN / 4 + (XSCREEN * 3 / 4 - XSCREEN / 4 - playRectWidth) / 2, YSCREEN - 100, XSCREEN / 4 + (XSCREEN * 3 / 4 - XSCREEN / 4 - playRectWidth) / 2 + playRectWidth, YSCREEN - 100 + playRectHeight, 5, 5, al_map_rgb(255, 255, 255)); // Biały prostokąt dla opcji "PLAY" z zaokrąglonymi rogami
		al_draw_rounded_rectangle(XSCREEN / 4 + (XSCREEN * 3 / 4 - XSCREEN / 4 - playRectWidth) / 2, YSCREEN - 100, XSCREEN / 4 + (XSCREEN * 3 / 4 - XSCREEN / 4 - playRectWidth) / 2 + playRectWidth, YSCREEN - 100 + playRectHeight, 5, 5, al_map_rgb(0, 0, 0), 2); // Czarna obwódka dla opcji "PLAY" z zaokrąglonymi rogami
		al_draw_text(font, (choice == 3) ? al_map_rgb(0, 0, 0) : al_map_rgb(100, 100, 100), XSCREEN / 2, YSCREEN - 100 + playRectHeight / 2 - al_get_font_line_height(font) / 2, ALLEGRO_ALIGN_CENTER, "PLAY"); // Czarny tekst dla opcji 3, szary dla pozostałych, wyśrodkowany pionowo w prostokącie
		al_flip_display();

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) {
				choice = (choice != 1) ? choice - 1 : 3;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) {
				choice = (choice != 3) ? choice + 1 : 1;
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
					*playerNumber = rand() % 2 + 2;
					*map = rand() % 12 + 1;
					*gamework = true;
					*work = false;
					return;
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { // Przejście do menu głównego po wciśnięciu klawisza Escape
				*work = false;
				return;
			}
		}
	}
}

void mainMenu(int* playerNumber, int* map, bool* gamework, bool* APPWORK) {
	static int choice = 1;
	bool work = true;

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
					drawChoiceMenu(gamework, &work, playerNumber, map); // Poprawiono ten wiersz
					break;
				case 2: // INFO
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

		if (!gamework) mainMenu(&playerNumber, &map, &gamework, &APPWORK);
		else game(playerNumber, map); 
	};


	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}