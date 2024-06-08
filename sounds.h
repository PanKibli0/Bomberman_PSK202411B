#ifndef SOUND_H
#define SOUND_H
/**
 * @file sounds.h
 * @brief Plik nag��wkowy zawieraj�cy zadeklarowane d�wi�ki gry.
 */
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// Zewn�trzne deklaracje pr�bek d�wi�kowych
extern ALLEGRO_SAMPLE* mainSong; // G��wny utw�r muzyczny
extern ALLEGRO_SAMPLE* explosionSound; // D�wi�k eksplozji
extern ALLEGRO_SAMPLE* hitSound; // D�wi�k trafienia
extern ALLEGRO_SAMPLE* powerUpSound; // D�wi�k aktywacji PowerUp'a

/**
 * @brief Funkcja odpowiedzialna za wczytanie pr�bek d�wi�kowych.
 */
void loadSounds();

#endif // SOUND_H