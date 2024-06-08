#ifndef PLAYER_H
#define PLAYER_H
/**
 * @file player.h
 * @brief Zawiera struktury powi¹zane z graczem i obs³uguje gracza.
 */
#include "config.h"
#include "block.h"

struct Bomb;

/**
 * @brief Struktura przechowuj¹ca dane o bombach.
 */
typedef struct {
    int bombAmount; /**< Iloœæ bomb */
    float bombTime; /**< Czas wybuchu bomby */
    int BombPower; /**< Si³a eksplozji bomby */
} BombData;

/**
 * @brief Struktura przechowuj¹ca dane o power-upach.
 */
typedef struct {
    bool kick; /**< Czy gracz potrafi kopaæ bomby */
    struct { bool active; bool hold; } bombThief; /**< Czy gracz mo¿e chwytaæ aktywowane bomby */
    bool randomTeleport; /**< Czy gracz mo¿e wykonaæ losow¹ teleportacjê */
    float invisibility; /**< Czy gracz jest niewidzialny */
    float shieldTime; /**< Czas trwania tarczy chroni¹cej przed obra¿eniami */
} PowerUpData;

/**
 * @brief Struktura przechowuj¹ca dane gracza.
 */
typedef struct {
    int health; /**< Zdrowie gracza */
    Position position; /**< Pozycja gracza */
    ALLEGRO_BITMAP* graphic; /**< Grafika gracza */
    float velocity; /**< Prêdkoœæ gracza */
    BombData bombs; /**< Dane dotycz¹ce bomb gracza */
    PowerUpData activePower; /**< Aktywny power-up gracza */
    int direction; /**< Kierunek ruchu gracza (góra, dó³, lewo, prawo) */
    int frame; /**< Numer ramki grafiki gracza */
    ALLEGRO_COLOR color; /**< Kolor gracza */
    int controlKeys[6]; /**< Klawisze sterowania */
} Player;

/**
 * Inicjuje gracza.
 * @param players WskaŸnik na tablicê graczy
 * @param playerIndex Indeks gracza do zainicjowania
 * @param health Zdrowie pocz¹tkowe gracza
 * @param x Wspó³rzêdna X pozycji startowej gracza
 * @param y Wspó³rzêdna Y pozycji startowej gracza
 * @param velocity Prêdkoœæ gracza
 * @param bombAmount Iloœæ bomb, które gracz mo¿e postawiæ jednoczeœnie
 * @param bombPower Si³a eksplozji bomb
 * @param color Kolor gracza
 * @param controlKeys Tablica klawiszy sterowania
 */
void initPlayer(Player* players, int playerIndex, unsigned int health, int x, int y, float velocity, int bombAmount, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);

/**
 * Rysuje gracza na ekranie.
 * @param player WskaŸnik na gracza do narysowania
 * @param playerNumber Numer gracza
 * @param gameDisplay Bitmapa ekranu gry
 */
void drawPlayer(Player* player, int playerNumber, ALLEGRO_BITMAP* gameDisplay);

/**
 * Porusza gracza na podstawie stanu klawiatury.
 * @param player WskaŸnik na gracza do poruszenia
 * @param playerNumber Numer gracza
 * @param keyState Stan klawiatury
 * @param block Blok
 * @param bomb Bomba
 */
void movePlayer(Player* player, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, struct Bomb* bomb);

/**
 * Umieszcza bombê na mapie.
 * @param players WskaŸnik na tablicê graczy
 * @param playerNumber Numer gracza
 * @param bomb WskaŸnik na bombê
 * @param keyState Stan klawiatury
 */
void placeBomb(Player* players, int playerNumber, struct Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState);

#endif /* PLAYER_H */
