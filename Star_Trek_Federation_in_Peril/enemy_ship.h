#ifndef ENEMY_SHIP_H_INCLUDED
#define ENEMY_SHIP_H_INCLUDED

#include "game_attributes.h"
#include "data_transfer_types.h"

#include <stdbool.h>

#include "debugmalloc.h"

typedef struct enemyship{
    int y_coor;
    int x_coor;
    int speed;
    int health;
    int damage;
    ///char *avatar_path;
}EnemyShip;

typedef struct enemysquadronship{
    EnemyShip ship;
    struct enemysquadronship *next_ship;
    struct enemysquadronship *prev_ship;
}EnemySquadronShip;

typedef struct enemyarmada{
    int number_of_squadrons;
    EnemySquadronShip **enemy_armada;
    int *squadron_dirs;
    int *squadron_heights;
    bool *entry_finished_per_squadron;
    bool ready_to_move;
}EnemyArmada;


#endif // ENEMY_SHIP_H_INCLUDED
