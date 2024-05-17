#ifndef POSITION_H
#define POSITION_H

#include <allegro5/allegro.h>

#define FPS 120
#define TILE 80
#define XNUMBER 19
#define YNUMBER 11
#define PLAYERS 2
#define XSCREEN 1920
#define YSCREEN 1080


typedef struct {
    int x, y;
} Position;

#endif /* POSITION_H */