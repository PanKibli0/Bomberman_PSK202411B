#ifndef PLAYER_H
#define PLAYER_H
/**
 * @file player.h
 * @brief Zawiera struktury powi�zane z graczem i obs�uguje gracza.
 */
#include "config.h"
#include "block.h"

struct Bomb;

/**
 * @brief Struktura przechowuj�ca dane o bombach.
 */
typedef struct {
    int bombAmount; /**< Ilo�� bomb */
    float bombTime; /**< Czas wybuchu bomby */
    int BombPower; /**< Si�a eksplozji bomby */
} BombData;

/**
 * @brief Struktura przechowuj�ca dane o power-upach.
 */
typedef struct {
    bool kick; /**< Czy gracz potrafi kopa� bomby */
    struct { bool active; bool hold; } bombThief; /**< Czy gracz mo�e chwyta� aktywowane bomby */
    bool randomTeleport; /**< Czy gracz mo�e wykona� losow� teleportacj� */
    float invisibility; /**< Czy gracz jest niewidzialny */
    float shieldTime; /**< Czas trwania tarczy chroni�cej przed obra�eniami */
} PowerUpData;

/**
 * @brief Struktura przechowuj�ca dane gracza.
 */
typedef struct {
    int health; /**< Zdrowie gracza */
    Position position; /**< Pozycja gracza */
    ALLEGRO_BITMAP* graphic; /**< Grafika gracza */
    float velocity; /**< Pr�dko�� gracza */
    BombData bombs; /**< Dane dotycz�ce bomb gracza */
    PowerUpData activePower; /**< Aktywny power-up gracza */
    int direction; /**< Kierunek ruchu gracza (g�ra, d�, lewo, prawo) */
    int frame; /**< Numer ramki grafiki gracza */
    ALLEGRO_COLOR color; /**< Kolor gracza */
    int controlKeys[6]; /**< Klawisze sterowania */
} Player;

/**
 * Inicjuje gracza.
 * @param players Wska�nik na tablic� graczy
 * @param playerIndex Indeks gracza do zainicjowania
 * @param health Zdrowie pocz�tkowe gracza
 * @param x Wsp�rz�dna X pozycji startowej gracza
 * @param y Wsp�rz�dna Y pozycji startowej gracza
 * @param velocity Pr�dko�� gracza
 * @param bombAmount Ilo�� bomb, kt�re gracz mo�e postawi� jednocze�nie
 * @param bombPower Si�a eksplozji bomb
 * @param color Kolor gracza
 * @param controlKeys Tablica klawiszy sterowania
 */
void initPlayer(Player* players, int playerIndex, unsigned int health, int x, int y, float velocity, int bombAmount, int bombPower, ALLEGRO_COLOR color, int controlKeys[5]);

/**
 * Rysuje gracza na ekranie.
 * @param player Wska�nik na gracza do narysowania
 * @param playerNumber Numer gracza
 * @param gameDisplay Bitmapa ekranu gry
 */
void drawPlayer(Player* player, int playerNumber, ALLEGRO_BITMAP* gameDisplay);

/**
 * Porusza gracza na podstawie stanu klawiatury.
 * @param player Wska�nik na gracza do poruszenia
 * @param playerNumber Numer gracza
 * @param keyState Stan klawiatury
 * @param block Blok
 * @param bomb Bomba
 */
void movePlayer(Player* player, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* block, struct Bomb* bomb);

/**
 * Umieszcza bomb� na mapie.
 * @param players Wska�nik na tablic� graczy
 * @param playerNumber Numer gracza
 * @param bomb Wska�nik na bomb�
 * @param keyState Stan klawiatury
 */
void placeBomb(Player* players, int playerNumber, struct Bomb** bomb, ALLEGRO_KEYBOARD_STATE* keyState);

#endif /* PLAYER_H */
