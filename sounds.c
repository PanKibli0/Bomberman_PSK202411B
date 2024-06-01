#include "sounds.h"

ALLEGRO_SAMPLE* mainSong = NULL;
ALLEGRO_SAMPLE* explosionSound = NULL;
ALLEGRO_SAMPLE* hitSound = NULL;
ALLEGRO_SAMPLE* powerUpSound = NULL;

void loadSounds() {
    mainSong = al_load_sample("sounds/mainSong.mp3");
    explosionSound = al_load_sample("sounds/explosionSound.mp3");
    hitSound = al_load_sample("sounds/hitSound.mp3");
    powerUpSound = al_load_sample("sounds/powerUpSound.mp3");
}