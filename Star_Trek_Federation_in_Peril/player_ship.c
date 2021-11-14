#include "player_ship.h"
#include "input_state_interface.h"
#include "debugmalloc.h"

#include <stdbool.h>


PlayerShip *init_player_ship(int width, int hight, int health, int speed){
    PlayerShip *ps = (PlayerShip*) malloc(sizeof(PlayerShip));
    ps->x_coor = width/2;
    ps->y_coor = hight/4*3;
    ps->health = health;
    ps->speed = speed;
    return ps;
}

void move_player_ship(PlayerShip *ps, InputStateInterface *isi){
    if(isi->up){
        ps->y_coor -= ps->speed;
    }
    if(isi->down){
        ps->y_coor += ps->speed;
    }
    if(isi->left){
        ps->x_coor -= ps->speed;
    }
    if(isi->right){
        ps->x_coor += ps->speed;
    }
}

void free_player_ship(PlayerShip *ps){
    free(ps);
}
