#ifndef TORPEDO_H_INCLUDED
#define TORPEDO_H_INCLUDED

#include "game_attributes.h"

#include <stdbool.h>

#include "debugmalloc.h"

typedef struct colordata{
    int r;
    int g;
    int b;
    int a;
}ColorData;

typedef struct torpedocolors{
    ColorData outter_ring;
    ColorData inner_ring;
    ColorData center;
}TorpedoColors;

typedef struct torpedoshot{
    int x_coor;
    int y_coor;
    int damage;
    int speed;
    int dir;
    TorpedoColors colors;
    struct torpedoshot *next_torpedo;
    struct torpedoshot *prev_torpedo;
}TorpedoShot;

#endif // TORPEDO_H_INCLUDED
