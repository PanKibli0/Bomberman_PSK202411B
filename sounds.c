/**
 * @file sounds.c
 * @brief Plik wczytuj¹cy dŸwiêki.
 */
#include "sounds.h"

 // Inicjalizacja wskaŸników próbek dŸwiêkowych
ALLEGRO_SAMPLE* mainSong = NULL; // G³ówny utwór muzyczny
ALLEGRO_SAMPLE* explosionSound = NULL; // DŸwiêk eksplozji
ALLEGRO_SAMPLE* hitSound = NULL; // DŸwiêk trafienia
ALLEGRO_SAMPLE* powerUpSound = NULL; // DŸwiêk aktywacji PowerUp'a

/**
 * @brief Funkcja wczytuj¹ca próbki dŸwiêkowe z odpowiednich plików.
 *
 * Funkcja ta wczytuje próbki dŸwiêkowe z plików dŸwiêkowych o ustalonych nazwach
 * i przypisuje je do odpowiednich wskaŸników.
 */
void loadSounds() {
    mainSong = al_load_sample("sounds/mainSong.mp3"); // Wczytaj g³ówny utwór muzyczny
    explosionSound = al_load_sample("sounds/explosionSound.mp3"); // Wczytaj dŸwiêk eksplozji
    hitSound = al_load_sample("sounds/hitSound.mp3"); // Wczytaj dŸwiêk trafienia
    powerUpSound = al_load_sample("sounds/powerUpSound.mp3"); // Wczytaj dŸwiêk aktywacji PowerUp'a
}