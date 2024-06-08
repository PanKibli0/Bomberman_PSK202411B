#include "game.h"
/**
 * @file game.c
 * @brief Plik g³ówny obs³uguj¹cy grê.
 */
extern ALLEGRO_EVENT event; /**< Zmienna przechowuj¹ca ostatnie zdarzenie. */
extern ALLEGRO_DISPLAY* display; /**< WskaŸnik na ekran. */
extern ALLEGRO_EVENT_QUEUE* event_queue; /**< Kolejka zdarzeñ. */
extern ALLEGRO_KEYBOARD_STATE keyState; /**< Stan klawiatury. */
extern ALLEGRO_TIMER* timer; /**< Timer do zarz¹dzania czasem gry. */
extern ALLEGRO_FONT* font; /**< Czcionka do wyœwietlania tekstu. */

/**
 * @brief Odœwie¿a ekran gry.
 *
 * Funkcja odpowiedzialna za rysowanie elementów gry na ekranie.
 *
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 * @param blocks Lista bloków na planszy.
 * @param bombs Lista bomb na planszy.
 * @param players Tablica struktur graczy.
 * @param playerNumber Liczba graczy w grze.
 * @param explosions Lista eksplozji.
 * @param powerUps Lista bonusów na planszy.
 */
void gameRefresh(ALLEGRO_BITMAP* gameDisplay, Block* blocks, Bomb* bombs, Player* players, int playerNumber, Explosion* explosions, PowerUp* powerUps) {
    al_set_target_bitmap(gameDisplay);
    al_clear_to_color(al_map_rgb(96, 96, 96));

    drawBlocks(blocks, gameDisplay);
    drawPowerUps(powerUps, gameDisplay);
    drawBombs(bombs, gameDisplay);
    drawPlayer(players, playerNumber, gameDisplay);
    drawExplosion(explosions, gameDisplay);

}

/**
 * @brief Odœwie¿a wyœwietlany ekran.
 *
 * Funkcja odpowiedzialna za odœwie¿anie ekranu gry, w tym rysowanie
 * planszy gry oraz panelu informacyjnego.
 *
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 * @param infoPanel Bitmapa reprezentuj¹ca panel informacyjny.
 */
void displayRefreshing(ALLEGRO_BITMAP* gameDisplay, ALLEGRO_BITMAP* infoPanel) {
    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_filled_rectangle(0, 0, 1920, al_get_bitmap_height(gameDisplay), al_map_rgb(96, 96, 96));
    al_draw_bitmap(gameDisplay, (1920 - TILE * 19) / 2, 0, 0);
    al_draw_filled_rectangle(0, al_get_bitmap_height(gameDisplay), 1920, 1080, al_map_rgb(255, 252, 171));
    al_draw_bitmap(infoPanel, (1920 - TILE * 19) / 2, 11 * TILE, 0);

    al_flip_display();
}

/**
 * @brief Obs³uguje ekran zwyciêstwa.
 *
 * Funkcja odpowiedzialna za wyœwietlenie ekranu zwyciêstwa, na którym
 * wyœwietlane s¹ informacje o zwyciêzcy oraz opcje do wyboru.
 *
 * @param winnerIndex Indeks gracza, który zwyciê¿y³.
 * @param players Tablica struktur graczy.
 */
void victory(int winnerIndex, Player* players) {
    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_filled_rounded_rectangle(640, 360, 1280, 720, 100, 100, players[winnerIndex].color);
    al_draw_rounded_rectangle(640, 360, 1280, 720, 100, 100, al_map_rgb(0, 0, 0), 10);

    al_draw_filled_rounded_rectangle(710, 445, 1210, 525, 45, 45, al_map_rgb(192, 192, 192));
    al_draw_rounded_rectangle(710, 445, 1210, 525, 45, 45, al_map_rgb(0, 0, 0), 5);
    if (winnerIndex != -1) al_draw_textf(font, players[winnerIndex].color, 960, 470, ALLEGRO_ALIGN_CENTER, "Player %d won!", winnerIndex + 1);
    else (al_draw_text(font, al_map_rgb(0, 0, 0), 960, 470, ALLEGRO_ALIGN_CENTER, "No one won!"));

    al_draw_filled_rounded_rectangle(810, 565, 1110, 645, 45, 45, al_map_rgb(192, 192, 192));
    al_draw_rounded_rectangle(810, 565, 1110, 645, 45, 45, al_map_rgb(0, 0, 0), 5);
    al_draw_text(font, al_map_rgb(255, 255, 0), 960, 590, ALLEGRO_ALIGN_CENTER, "EXIT");

    al_flip_display();

    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN && (event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
            return;
        }
    }
}

/**
 * @brief Obs³uguje ekran zakoñczenia gry.
 *
 * Funkcja odpowiedzialna za wyœwietlenie ekranu zakoñczenia gry, na którym
 * wyœwietlane s¹ opcje do wyboru.
 *
 * @return Wartoœæ logiczna okreœlaj¹ca czy u¿ytkownik wybra³ powrót do menu g³ównego.
 */
bool endGame() {
    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_filled_rounded_rectangle(640, 360, 1280, 720, 100, 100, al_map_rgb(24, 110, 172));
    al_draw_rounded_rectangle(640, 360, 1280, 720, 100, 100, al_map_rgb(0, 0, 0), 10);

    al_draw_filled_rounded_rectangle(710, 445, 1210, 525, 45, 45, al_map_rgb(192, 192, 192));
    al_draw_rounded_rectangle(710, 445, 1210, 525, 45, 45, al_map_rgb(0, 0, 0), 5);
    al_draw_text(font, al_map_rgb(255, 255, 255), 960, 470, ALLEGRO_ALIGN_CENTER, "RETURN TO MAIN MENU");

    al_draw_filled_rounded_rectangle(810, 565, 1110, 645, 45, 45, al_map_rgb(192, 192, 192));
    al_draw_rounded_rectangle(810, 565, 1110, 645, 45, 45, al_map_rgb(0, 0, 0), 5);
    al_draw_text(font, al_map_rgb(255, 255, 0), 960, 590, ALLEGRO_ALIGN_CENTER, "EXIT");

    al_flip_display();

    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) return true;
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) return false;
        }
    }
}

/**
 * @brief G³ówna pêtla gry.
 *
 * Funkcja odpowiada za logikê g³ównej pêtli gry, w tym sterowanie graczami,
 * obs³ugê zdarzeñ, wykrywanie koñca gry i wyœwietlanie ekranów zwyciêstwa
 * lub zakoñczenia gry.
 *
 * @param playerNumber Liczba graczy w grze.
 * @param map Numer mapy.
 * @param gamework WskaŸnik do zmiennej okreœlaj¹cej czy gra jest w trakcie.
 */
void game(int playerNumber, int map, bool* gamework) {
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

            gameRefresh(gameDisplay, blocks, bombs, players, playerNumber, explosions, powerUps);
            drawInfoPanel(infoPanel, players, playerNumber);
            displayRefreshing(gameDisplay, infoPanel);

            int alivePlayers = 0;
            int winnerIndex = -1;
            for (int i = 0; i < playerNumber; ++i) {
                if (players[i].health > 0) {
                    alivePlayers++;
                    winnerIndex = i;
                }
                if (alivePlayers > 1) continue;
            }

            if (alivePlayers == 1) {
                *gamework = false;
                victory(winnerIndex, players);
                run = false;
            }
            else if (alivePlayers == 0) {
                *gamework = false;
                victory(-1, players);
                run = false;
            }

            if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                if (endGame()) {
                    *gamework = false;
                    run = false;
                }
                al_rest(0.1);
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
}