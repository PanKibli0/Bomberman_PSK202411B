#ifndef POWERUP_H
#define POWERUP_H
/**
 * @file powerup.h
 * @brief Plik zawieraj�cy informacje o powerupach i wywo�uj�cy je.
 */
#include <allegro5/allegro.h>
#include "config.h"
#include "player.h"
#include "bomb.h"

/**
 * @brief Typ wyliczeniowy okre�laj�cy rodzaje PowerUp'�w.
 */
typedef enum {
    HEALTH, /**< PowerUp zwi�kszaj�cy zdrowie. */
    BOMB_POWER_UP, /**< PowerUp zwi�kszaj�cy si�� bomby. */
    BOMB_POWER_DOWN, /**< PowerUp zmniejszaj�cy si�� bomby. */
    VELOCITY_UP, /**< PowerUp zwi�kszaj�cy pr�dko�� gracza. */
    VELOCITY_DOWN, /**< PowerUp zmniejszaj�cy pr�dko�� gracza. */
    BOMB_LIMIT_UP, /**< PowerUp zwi�kszaj�cy limit bomb. */
    BOMB_LIMIT_DOWN, /**< PowerUp zmniejszaj�cy limit bomb. */
    SHIELD, /**< PowerUp zapewniaj�cy tarcz� ochronn�. */
    INVISIBILITY, /**< PowerUp sprawiaj�cy, �e gracz staje si� niewidzialny. */
    KICK, /**< PowerUp umo�liwiaj�cy kopanie bomb. */
    BOMB_THIEF, /**< PowerUp pozwalaj�cy na zabranie postawionej bomby. */
    RANDOM_TELEPORT, /**< PowerUp umo�liwiaj�cy losow� teleportacj�. */
    TYPES_NUMBER /**< Liczba rodzaj�w PowerUp'�w. */
} PowerUpType;

/**
 * @brief Struktura reprezentuj�ca pojedynczy PowerUp.
 */
typedef struct PowerUp {
    Position position; /**< Pozycja PowerUp'a na planszy. */
    PowerUpType type; /**< Typ PowerUp'a. */
    float lifeTime; /**< Pozosta�y czas �ycia PowerUp'a. */
    ALLEGRO_BITMAP* graphic; /**< Grafika reprezentuj�ca PowerUp'a. */
    struct PowerUp* next; /**< Wska�nik na kolejny PowerUp. */
} PowerUp;

/**
 * @brief Funkcja tworz�ca nowe PowerUp'y na planszy.
 *
 * @param powerUps Podw�jny wska�nik na list� PowerUp'�w.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks Wska�nik na pocz�tek listy blok�w planszy.
 * @param bombs Wska�nik na pocz�tek listy bomb na planszy.
 */
void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs);

/**
 * @brief Funkcja rysuj�ca PowerUp'y na ekranie gry.
 *
 * @param powerUps Lista PowerUp'�w do narysowania.
 * @param gameDisplay Bitmapa reprezentuj�ca ekran gry.
 */
void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay);

/**
 * @brief Funkcja odpowiedzialna za zebranie PowerUp'a przez gracza.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param powerUps Podw�jny wska�nik na list� PowerUp'�w.
 */
void collectPowerUp(Player* players, int playerNumber, PowerUp** powerUps);

/**
 * @brief Funkcja odpowiadaj�ca za znikni�cie PowerUp'a po up�ywie czasu �ycia.
 *
 * @param powerUps Podw�jny wska�nik na list� PowerUp'�w.
 */
void disappearancePowerUp(PowerUp** powerUps);

/**
 * @brief Funkcja niszcz�ca dany PowerUp na li�cie PowerUp'�w.
 *
 * @param powerUps Podw�jny wska�nik na list� PowerUp'�w.
 * @param powerUp Wska�nik na PowerUp do zniszczenia.
 */
void destroyPowerUp(PowerUp** powerUps, PowerUp* powerUp);

/**
 * @brief Funkcja wykorzystuj�ca efekt danego PowerUp'a po jego zebraniu przez gracza.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param keyState Stan klawiatury.
 * @param blocks Wska�nik na pocz�tek listy blok�w na planszy.
 * @param bombs Wska�nik na pocz�tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'�w.
 */
void usePower(Player* players, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* blocks, Bomb** bombs, PowerUp* powerUps);

/**
 * @brief Funkcja obs�uguj�ca efekt PowerUp'a umo�liwiaj�cego kopanie bomb.
 *
 * @param player Gracz, kt�ry u�ywa PowerUp'a.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks Wska�nik na pocz�tek listy blok�w na planszy.
 * @param bombs Wska�nik na pocz�tek listy bomb na planszy.
 */
void powerKick(Player* player, Player* players, int playerNumber, Block* blocks, Bomb** bombs);

/**
 * @brief Funkcja obs�uguj�ca efekt PowerUp'a pozwalaj�cego na zabranie postawionej bomby.
 *
 * @param player Gracz, kt�ry u�ywa PowerUp'a.
 * @param bombs Wska�nik na pocz�tek listy bomb na planszy.
 */
void powerBombThief(Player* player, Bomb** bombs);

/**
 * @brief Funkcja obs�uguj�ca efekt PowerUp'a umo�liwiaj�cego losow� teleportacj�.
 *
 * @param player Gracz, kt�ry u�ywa PowerUp'a.
 * @param blocks Wska�nik na pocz�tek listy blok�w na planszy.
 * @param bombs Wska�nik na pocz�tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'�w.
 */
void powerTeleport(Player* player, Block* blocks, Bomb* bombs, PowerUp* powerUps);

#endif // POWERUP_H