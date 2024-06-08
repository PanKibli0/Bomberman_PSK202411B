#ifndef SOUND_H
#define SOUND_H
/**
 * @file sounds.h
 * @brief Plik nag³ówkowy zawieraj¹cy zadeklarowane dŸwiêki gry.
 */
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// Zewnêtrzne deklaracje próbek dŸwiêkowych
extern ALLEGRO_SAMPLE* mainSong; // G³ówny utwór muzyczny
extern ALLEGRO_SAMPLE* explosionSound; // DŸwiêk eksplozji
extern ALLEGRO_SAMPLE* hitSound; // DŸwiêk trafienia
extern ALLEGRO_SAMPLE* powerUpSound; // DŸwiêk aktywacji PowerUp'a

/**
 * @brief Funkcja odpowiedzialna za wczytanie próbek dŸwiêkowych.
 */
void loadSounds();

#endif // SOUND_H