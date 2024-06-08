#ifndef BOMB_H
#define BOMB_H
/**
 * @file bomb.h
 * @brief Plik implementuj�cy bomby i ich dzia�anie.
 */
#include "block.h"
#include "player.h"
#include "explosion.h"

/**
 * @brief Struktura reprezentuj�ca bomb� w grze.
 *
 * Struktura przechowuje informacje o pozycji bomby, jej graficznym przedstawieniu,
 * mocy wybuchu, czasie potrzebnym do wybuchu, wska�nik na kolejn� bomb� oraz wska�nik na w�a�ciciela bomby.
 */
typedef struct Bomb {
    Position position;          /**< Pozycja bomby */
    ALLEGRO_BITMAP* graphic;    /**< Graficzne przedstawienie bomby */
    int power;                  /**< Moc wybuchu bomby */
    float time;                 /**< Czas do wybuchu bomby */
    struct Bomb* next;          /**< Wska�nik na nast�pn� bomb� w li�cie */
    Player* owner;              /**< W�a�ciciel bomby */
} Bomb;

/**
 * @brief Dodaje now� bomb� do listy bomb.
 *
 * Funkcja sprawdza, czy na pozycji (x, y) nie jest ju� ustawiona bomba,
 * a nast�pnie tworzy now� bomb�, ustawia jej pozycj�, moc, czas do wybuchu,
 * w�a�ciciela oraz grafik�. Dodaje now� bomb� na pocz�tek listy bomb.
 *
 * @param bomb Podw�jny wska�nik na pocz�tek listy bomb na planszy.
 * @param x Pozycja x nowej bomby.
 * @param y Pozycja y nowej bomby.
 * @param power Moc wybuchu nowej bomby.
 * @param owner Wska�nik na w�a�ciciela nowej bomby.
 * @return true je�li dodanie bomby powiod�o si�, false w przeciwnym wypadku.
 */
bool addBomb(Bomb** head, int x, int y, int power, Player* owner);

/**
 * @brief Ustawia bomby na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekranie i ustawia wszystkie bomby
 * z listy bomb w odpowiednich pozycjach.
 *
 * @param bomb Wska�nik na pocz�tek listy bomb na planszy.
 * @param gameDisplay Bitmapa reprezentuj�ca ekran gry.
 */
void drawBombs(Bomb* head, ALLEGRO_BITMAP* gameDisplay);

/**
 * @brief Aktualizuje stan bomb i sprawdza, czy kt�ra� z nich powinna wybuchn��.
 *
 * Funkcja zmniejsza czas do wybuchu ka�dej bomby, a je�li czas bomby up�yn��,
 * powoduje jej wybuch, usuwaj�c j� z listy bomb, niszcz�c bloki, rani�c graczy
 * oraz generuj�c wybuch.
 *
 * @param bombs Podw�jny wska�nik na pocz�tek listy bomb na planszy.
 * @param blocks Wska�nik na pocz�tek listy blok�w na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podw�jny wska�nik na pocz�tek listy wybuch�w.
 */
void timerBomb(Bomb** bomb, Block* blocks, Player* players, int playerNumber, Explosion** explosions);

#endif /* BOMB_H */