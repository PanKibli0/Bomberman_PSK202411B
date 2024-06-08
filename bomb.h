#ifndef BOMB_H
#define BOMB_H
/**
 * @file bomb.h
 * @brief Plik implementuj¹cy bomby i ich dzia³anie.
 */
#include "block.h"
#include "player.h"
#include "explosion.h"

/**
 * @brief Struktura reprezentuj¹ca bombê w grze.
 *
 * Struktura przechowuje informacje o pozycji bomby, jej graficznym przedstawieniu,
 * mocy wybuchu, czasie potrzebnym do wybuchu, wskaŸnik na kolejn¹ bombê oraz wskaŸnik na w³aœciciela bomby.
 */
typedef struct Bomb {
    Position position;          /**< Pozycja bomby */
    ALLEGRO_BITMAP* graphic;    /**< Graficzne przedstawienie bomby */
    int power;                  /**< Moc wybuchu bomby */
    float time;                 /**< Czas do wybuchu bomby */
    struct Bomb* next;          /**< WskaŸnik na nastêpn¹ bombê w liœcie */
    Player* owner;              /**< W³aœciciel bomby */
} Bomb;

/**
 * @brief Dodaje now¹ bombê do listy bomb.
 *
 * Funkcja sprawdza, czy na pozycji (x, y) nie jest ju¿ ustawiona bomba,
 * a nastêpnie tworzy now¹ bombê, ustawia jej pozycjê, moc, czas do wybuchu,
 * w³aœciciela oraz grafikê. Dodaje now¹ bombê na pocz¹tek listy bomb.
 *
 * @param bomb Podwójny wskaŸnik na pocz¹tek listy bomb na planszy.
 * @param x Pozycja x nowej bomby.
 * @param y Pozycja y nowej bomby.
 * @param power Moc wybuchu nowej bomby.
 * @param owner WskaŸnik na w³aœciciela nowej bomby.
 * @return true jeœli dodanie bomby powiod³o siê, false w przeciwnym wypadku.
 */
bool addBomb(Bomb** head, int x, int y, int power, Player* owner);

/**
 * @brief Ustawia bomby na ekranie gry.
 *
 * Funkcja ustawia cel rysowania na ekranie i ustawia wszystkie bomby
 * z listy bomb w odpowiednich pozycjach.
 *
 * @param bomb WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 */
void drawBombs(Bomb* head, ALLEGRO_BITMAP* gameDisplay);

/**
 * @brief Aktualizuje stan bomb i sprawdza, czy któraœ z nich powinna wybuchn¹æ.
 *
 * Funkcja zmniejsza czas do wybuchu ka¿dej bomby, a jeœli czas bomby up³yn¹³,
 * powoduje jej wybuch, usuwaj¹c j¹ z listy bomb, niszcz¹c bloki, rani¹c graczy
 * oraz generuj¹c wybuch.
 *
 * @param bombs Podwójny wskaŸnik na pocz¹tek listy bomb na planszy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param explosions Podwójny wskaŸnik na pocz¹tek listy wybuchów.
 */
void timerBomb(Bomb** bomb, Block* blocks, Player* players, int playerNumber, Explosion** explosions);

#endif /* BOMB_H */