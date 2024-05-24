#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <stdio.h>
#include "graphics.h"

ALLEGRO_EVENT event;
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* font;


void drawMainMenu(ALLEGRO_BITMAP* background) {
	
	ALLEGRO_BITMAP* logo = al_load_bitmap("graphics/logo.png");
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_bitmap(logo, 465, 0, 0);
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
		const char* playerOptions[] = { "2 Players", "3 Players", "4 Players" };

		al_draw_filled_rounded_rectangle(410, 60, 1510, 140, 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(410, 60, 1510, 140, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 650, 85, ALLEGRO_ALIGN_LEFT, "CHOOSE NUMBER OF PLAYERS:");

		for (int i = 0; i < 3; i++) {
			ALLEGRO_COLOR textColor = (choice == 1) ? ((i + 2 == *playerNumber) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255)) : ((i + 2 == *playerNumber) ? al_map_rgb(0, 0, 255) : al_map_rgb(255, 255, 255));
			al_draw_filled_rounded_rectangle(410 + i * 400, 150, 710 + i * 400, 230, 45, 45, al_map_rgb(192, 192, 192));
			al_draw_rounded_rectangle(410 + i * 400, 150, 710 + i * 400, 230, 45, 45, al_map_rgb(0, 0, 0), 5);
			al_draw_text(font, textColor, 560 + i * 400, 175, ALLEGRO_ALIGN_CENTER, playerOptions[i]);
		}

		// Mapa
		al_draw_filled_rounded_rectangle(410, 270, 1510, 350, 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(410, 270, 1510, 350, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == 2) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 810, 295, ALLEGRO_ALIGN_LEFT, "CHOOSE A MAP:");

		// Przycisk Random
		ALLEGRO_COLOR randomTextColor = (choice == 2 && *map == 0) ? al_map_rgb(255, 255, 0) : (choice != 2 && *map == 0) ? al_map_rgb(0, 0, 255) : al_map_rgb(255, 255, 255);
		al_draw_filled_rounded_rectangle(610, 360, 1310, 440, 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(610, 360, 1310, 440, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, randomTextColor, 960, 385, ALLEGRO_ALIGN_CENTER, "Random");

		// Przycisk map
		const char* mapNames[] = { "Standard", "Circular", "Hard Way", "Halfline", "Crossed Fate", "Centerbox", "Lines", "Breakland", "Crossroads", "Pincers", "Empty Cross", "Empty" };

		for (int i = 0; i < 12; i++) {
			ALLEGRO_COLOR mapTextColor = (choice == 2 && *map == i + 1) ? al_map_rgb(255, 255, 0) : (choice != 2 && *map == i + 1) ? al_map_rgb(0, 0, 255) : al_map_rgb(255, 255, 255);
			int row = i / 3;
			int col = i % 3;
			int x = 410 + col * 400;
			int y = 460 + row * 100;
			al_draw_filled_rounded_rectangle(x, y, x + 300, y + 80, 45, 45, al_map_rgb(192, 192, 192));
			al_draw_rounded_rectangle(x, y, x + 300, y + 80, 45, 45, al_map_rgb(0, 0, 0), 5);
			al_draw_text(font, mapTextColor, x + 150, y + 25, ALLEGRO_ALIGN_CENTER, mapNames[i]);
		}

		// START
		al_draw_filled_rounded_rectangle(610, 900, 1310, 980, 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(610, 900, 1310, 980, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_text(font, (choice == 3) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 960, 925, ALLEGRO_ALIGN_CENTER, "PLAY");

		al_flip_display();


		// DZIALANIE
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (choice) {
			case 1:
				if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
					*playerNumber = (*playerNumber > 2) ? *playerNumber - 1 : 4;
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
					*playerNumber = (*playerNumber < 4) ? *playerNumber + 1 : 2;
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					choice = 2;
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					drawMainMenu(background);
					return;
				}
				break;
			case 2:
				if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) {
					if (*map == 1 || *map == 2 || *map == 3) {
						*map = 0;
					}
					else if (*map == 0) {
						*map = 12;
					}
					else if (*map > 3) {
						*map -= 3;
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) {
					if (*map == 0) {
						*map = 1;
					}
					else if (*map < 10) {
						*map += 3;
					}
					else if (*map == 12) {
						*map = 0;
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
					if (*map > 0) {
						--(*map);
					}
					else {
						*map = 12;
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
					if (*map < 12) {
						++(*map);
					}
					else {
						*map = 0;
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					if (choice == 2) {
						choice = 3;
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					choice = 1;
				}
				break;
			case 3:
				if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					if (*map == 0) *map = rand() % 12 + 1;
					*gamework = true;
					*work = false;
					return;
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					choice = 2;
				}
				break;
			}
		}
	}
	al_destroy_bitmap(background);
}



void infoMenu(ALLEGRO_BITMAP* background) {
	int choice = 1;
	ALLEGRO_FONT* fontInfo = al_load_font("graphics/font.ttf", 25, 0);
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(background, 0, 0, 0);


	ALLEGRO_BITMAP* graphics[] = {
		powerBombPowerUpGraphic,
		powerBombPowerDownGraphic,
		powerVelocityUpGraphic,
		powerVelocityDownGraphic,
		powerBombLimitUpGraphic,
		powerBombLimitDownGraphic,
		powerHealthGraphic,
		powerShieldGraphic,
		powerInvisibilityGraphic,
		powerKickGraphic,
		powerBombThiefGraphic,
		powerRandomTeleportGraphic
	};

	int numGraphics = sizeof(graphics) / sizeof(graphics[0]);
	const char* descriptions[] = {
		"Increases bomb power.",
		"Decreases bomb power (cannot go below one).",
		"Increases player's speed.",
		"Decreases player's speed.",
		"Increases bomb limit.",
		"Decreases bomb limit (cannot go below one).",
		"Adds one heart.",
		"Provides a shield for a short time.",
		"Grants invisibility for a short time.",
		"Press skill button to kick a bomb as far as possible \nin the player's direction.",
		"Press skill button to steal a bomb placed next to the player \nin the player's direction.",
		"Press skill button to teleport to a random location. \n(One-time use)"
	};

	for (int i = 0; i < numGraphics; ++i) {
		int col = i % 2;
		int row = i / 2;

		int rectX = 85 + col * 931;
		int rectY = 100 + row * 136;

		al_draw_bitmap(graphics[i], rectX, rectY, 0);
		al_draw_filled_rounded_rectangle(rectX + 106, 100 + row * 136, rectX + 806, 196 + row * 136, 45, 45, al_map_rgb(192, 192, 192));
		al_draw_rounded_rectangle(rectX + 106, 100 + row * 136, rectX + 806, 196 + row * 136, 45, 45, al_map_rgb(0, 0, 0), 5);
		al_draw_textf(fontInfo, al_map_rgb(255, 255, 255), rectX + 456, 135 + row * 136, ALLEGRO_ALIGN_CENTER, "%s\n%", descriptions[i]);
	}

	
	/*
	al_draw_filled_rounded_rectangle(585, 940, 885, 1020, 45, 45, al_map_rgb(192, 192, 192)); 
	al_draw_rounded_rectangle(585, 940, 885, 1020, 45, 45, al_map_rgb(0, 0, 0), 5);
	al_draw_text(font, (choice == 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 735, 965, ALLEGRO_ALIGN_CENTER, "GENERAL");

 
	al_draw_filled_rounded_rectangle(1015, 940, 1315, 1020, 45, 45, al_map_rgb(192, 192, 192));
	al_draw_rounded_rectangle(1015, 940, 1315, 1020, 45, 45, al_map_rgb(0, 0, 0), 5);
	al_draw_text(font, (choice == 2) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 1165, 965, ALLEGRO_ALIGN_CENTER, "POWER-UPS");
	*/

	al_flip_display();

	while (1) {
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				drawMainMenu(background);
				
				return;
			}
		}
	}
}

void mainMenu(int* playerNumber, int* map, bool* gamework, bool* APPWORK) {
	static int choice = 1;
	bool work = true;
	ALLEGRO_BITMAP* background = al_load_bitmap("graphics/background.png");
	drawMainMenu(background);

	while (work) {
		
		al_set_target_bitmap(al_get_backbuffer(display));

		const char* options[] = { "START", "INFO", "EXIT" };

		for (int i = 0; i < 3; i++) {
			al_draw_filled_rounded_rectangle(810, 420 + i * 100, 1110, 500 + i * 100, 45, 45, al_map_rgb(192, 192, 192));
			al_draw_rounded_rectangle(810, 420 + i * 100, 1110, 500 + i * 100, 45, 45, al_map_rgb(0, 0, 0), 5);
			al_draw_text(font, (choice == i + 1) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255), 960, 445 + i * 100, ALLEGRO_ALIGN_CENTER, options[i]);
		}
		al_flip_display();

		al_wait_for_event(event_queue, &event);
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
				case 1: // START
					ChooseMenu(gamework, &work, playerNumber, map, background);
					break;
				case 2: // INFO
					infoMenu(background);
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
	loadGraphics();

	while (APPWORK) {
		al_wait_for_event(event_queue, &event);
		al_get_keyboard_state(&keyState);

		if (!gamework) { mainMenu(&playerNumber, &map, &gamework, &APPWORK); }
		else {
			
			game(playerNumber, map, &gamework);
		}
	};


	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);

	return 0;
}