#ifndef POWERUP_H
#define POWERUP_H
/**
 * @file powerup.h
 * @brief Plik zawieraj¹cy informacje o powerupach i wywo³uj¹cy je.
 */
#include <allegro5/allegro.h>
#include "config.h"
#include "player.h"
#include "bomb.h"

/**
 * @brief Typ wyliczeniowy okreœlaj¹cy rodzaje PowerUp'ów.
 */
typedef enum {
    HEALTH, /**< PowerUp zwiêkszaj¹cy zdrowie. */
    BOMB_POWER_UP, /**< PowerUp zwiêkszaj¹cy si³ê bomby. */
    BOMB_POWER_DOWN, /**< PowerUp zmniejszaj¹cy si³ê bomby. */
    VELOCITY_UP, /**< PowerUp zwiêkszaj¹cy prêdkoœæ gracza. */
    VELOCITY_DOWN, /**< PowerUp zmniejszaj¹cy prêdkoœæ gracza. */
    BOMB_LIMIT_UP, /**< PowerUp zwiêkszaj¹cy limit bomb. */
    BOMB_LIMIT_DOWN, /**< PowerUp zmniejszaj¹cy limit bomb. */
    SHIELD, /**< PowerUp zapewniaj¹cy tarczê ochronn¹. */
    INVISIBILITY, /**< PowerUp sprawiaj¹cy, ¿e gracz staje siê niewidzialny. */
    KICK, /**< PowerUp umo¿liwiaj¹cy kopanie bomb. */
    BOMB_THIEF, /**< PowerUp pozwalaj¹cy na zabranie postawionej bomby. */
    RANDOM_TELEPORT, /**< PowerUp umo¿liwiaj¹cy losow¹ teleportacjê. */
    TYPES_NUMBER /**< Liczba rodzajów PowerUp'ów. */
} PowerUpType;

/**
 * @brief Struktura reprezentuj¹ca pojedynczy PowerUp.
 */
typedef struct PowerUp {
    Position position; /**< Pozycja PowerUp'a na planszy. */
    PowerUpType type; /**< Typ PowerUp'a. */
    float lifeTime; /**< Pozosta³y czas ¿ycia PowerUp'a. */
    ALLEGRO_BITMAP* graphic; /**< Grafika reprezentuj¹ca PowerUp'a. */
    struct PowerUp* next; /**< WskaŸnik na kolejny PowerUp. */
} PowerUp;

/**
 * @brief Funkcja tworz¹ca nowe PowerUp'y na planszy.
 *
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 */
void createPowerUp(PowerUp** powerUps, Player* players, int playerNumber, Block* blocks, Bomb* bombs);

/**
 * @brief Funkcja rysuj¹ca PowerUp'y na ekranie gry.
 *
 * @param powerUps Lista PowerUp'ów do narysowania.
 * @param gameDisplay Bitmapa reprezentuj¹ca ekran gry.
 */
void drawPowerUps(PowerUp* powerUps, ALLEGRO_BITMAP* gameDisplay);

/**
 * @brief Funkcja odpowiedzialna za zebranie PowerUp'a przez gracza.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 */
void collectPowerUp(Player* players, int playerNumber, PowerUp** powerUps);

/**
 * @brief Funkcja odpowiadaj¹ca za znikniêcie PowerUp'a po up³ywie czasu ¿ycia.
 *
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 */
void disappearancePowerUp(PowerUp** powerUps);

/**
 * @brief Funkcja niszcz¹ca dany PowerUp na liœcie PowerUp'ów.
 *
 * @param powerUps Podwójny wskaŸnik na listê PowerUp'ów.
 * @param powerUp WskaŸnik na PowerUp do zniszczenia.
 */
void destroyPowerUp(PowerUp** powerUps, PowerUp* powerUp);

/**
 * @brief Funkcja wykorzystuj¹ca efekt danego PowerUp'a po jego zebraniu przez gracza.
 *
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param keyState Stan klawiatury.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'ów.
 */
void usePower(Player* players, int playerNumber, ALLEGRO_KEYBOARD_STATE* keyState, Block* blocks, Bomb** bombs, PowerUp* powerUps);

/**
 * @brief Funkcja obs³uguj¹ca efekt PowerUp'a umo¿liwiaj¹cego kopanie bomb.
 *
 * @param player Gracz, który u¿ywa PowerUp'a.
 * @param players Tablica graczy.
 * @param playerNumber Liczba graczy.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 */
void powerKick(Player* player, Player* players, int playerNumber, Block* blocks, Bomb** bombs);

/**
 * @brief Funkcja obs³uguj¹ca efekt PowerUp'a pozwalaj¹cego na zabranie postawionej bomby.
 *
 * @param player Gracz, który u¿ywa PowerUp'a.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 */
void powerBombThief(Player* player, Bomb** bombs);

/**
 * @brief Funkcja obs³uguj¹ca efekt PowerUp'a umo¿liwiaj¹cego losow¹ teleportacjê.
 *
 * @param player Gracz, który u¿ywa PowerUp'a.
 * @param blocks WskaŸnik na pocz¹tek listy bloków na planszy.
 * @param bombs WskaŸnik na pocz¹tek listy bomb na planszy.
 * @param powerUps Lista PowerUp'ów.
 */
void powerTeleport(Player* player, Block* blocks, Bomb* bombs, PowerUp* powerUps);

#endif // POWERUP_H