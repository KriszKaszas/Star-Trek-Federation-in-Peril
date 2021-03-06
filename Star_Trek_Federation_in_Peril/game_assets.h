#ifndef GAME_ASSETS_H_INCLUDED
#define GAME_ASSETS_H_INCLUDED

#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"
#include "torpedo.h"

typedef struct gameassets{
    StarMap *star_map;
    PlayerShip *player_ship;
    EnemyArmada *enemy_armada;
    TorpedoShot *player_torpedo;
    TorpedoShot *quantum_torpedo;
    TorpedoShot *enemy_torpedo;
}GameAssets;

#endif // GAME_ASSETS_H_INCLUDED
