/**
 * @file sounds.c
 * @brief Plik wczytuj�cy d�wi�ki.
 */
#include "sounds.h"

 // Inicjalizacja wska�nik�w pr�bek d�wi�kowych
ALLEGRO_SAMPLE* mainSong = NULL; // G��wny utw�r muzyczny
ALLEGRO_SAMPLE* explosionSound = NULL; // D�wi�k eksplozji
ALLEGRO_SAMPLE* hitSound = NULL; // D�wi�k trafienia
ALLEGRO_SAMPLE* powerUpSound = NULL; // D�wi�k aktywacji PowerUp'a

/**
 * @brief Funkcja wczytuj�ca pr�bki d�wi�kowe z odpowiednich plik�w.
 *
 * Funkcja ta wczytuje pr�bki d�wi�kowe z plik�w d�wi�kowych o ustalonych nazwach
 * i przypisuje je do odpowiednich wska�nik�w.
 */
void loadSounds() {
    mainSong = al_load_sample("sounds/mainSong.mp3"); // Wczytaj g��wny utw�r muzyczny
    explosionSound = al_load_sample("sounds/explosionSound.mp3"); // Wczytaj d�wi�k eksplozji
    hitSound = al_load_sample("sounds/hitSound.mp3"); // Wczytaj d�wi�k trafienia
    powerUpSound = al_load_sample("sounds/powerUpSound.mp3"); // Wczytaj d�wi�k aktywacji PowerUp'a
}