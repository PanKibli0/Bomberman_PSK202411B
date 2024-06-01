#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

extern ALLEGRO_SAMPLE* mainSong;
extern ALLEGRO_SAMPLE* explosionSound;
extern ALLEGRO_SAMPLE* hitSound;
extern ALLEGRO_SAMPLE* powerUpSound;

void loadSounds();

#endif // SOUND_H