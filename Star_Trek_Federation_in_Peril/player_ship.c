#include "player_ship.h"

#include <stdbool.h>

#include "debugmalloc.h"



PlayerShip *init_player_ship(int width, int height, int health, int speed){
    PlayerShip *ps = (PlayerShip*) malloc(sizeof(PlayerShip));
    BeamColor core = {253, 241, 191, 255};
    BeamColor falloff = {61, 119, 69, 220};
    Beam beam_comp = {core, falloff};

    ps->x_coor = width/2;
    ps->y_coor = height/4*3;
    ps->health = health;
    ps->speed = speed;
    ps->phaser_timer = 0;
    PhaserBeam *PhaserBeam = phaser_init(beam_comp, ps->x_coor, ps->y_coor);
    ps->phaser_blast = PhaserBeam;
    return ps;
}

void move_player_ship(PlayerShip *ps, InputStateInterface *isi, int width, int height){
    if(isi->up && ps->y_coor > 0){
        ps->y_coor -= ps->speed;
        ps->phaser_blast->beg_y -= ps->speed;
    }
    if(isi->down &&  ps->y_coor < height){
        ps->y_coor += ps->speed;
        ps->phaser_blast->beg_y += ps->speed;
    }
    if(isi->left && ps->x_coor > 0){
        ps->x_coor -= ps->speed;
        ps->phaser_blast->beg_x -= ps->speed;
    }
    if(isi->right && ps->x_coor  < width){
        ps->x_coor += ps->speed;
        ps->phaser_blast->beg_x += ps->speed;
    }
}

/**
*@brief fire_phaser
*@details Kilõ egy fézersugarat.
*@param [in out] isi pointer to an InputStateInterface type
*@param [in out] ps pointer to a PlayerShip type
*@param [in] elapsed_interval marker of elapsed ticks since program started
*@return void
*/

void fire_phaser(InputStateInterface *isi, PlayerShip *ps, int elapsed_interval){
    ps->phaser_blast->end_x = isi->mouse_position.mouse_x;
    ps->phaser_blast->end_y = isi->mouse_position.mouse_y;
    ps->phaser_timer = elapsed_interval;
    isi->phaser_firing = true;
}

void free_player_ship(PlayerShip *ps){
    free(ps->phaser_blast);
    free(ps);
}
