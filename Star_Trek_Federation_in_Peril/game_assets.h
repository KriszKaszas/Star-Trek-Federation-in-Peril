#ifndef GAME_ASSETS_H_INCLUDED
#define GAME_ASSETS_H_INCLUDED

#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"

typedef struct gameassets{
    StarMap *star_map;
    PlayerShip *player_ship;
    EnemyArmada *enemy_armada;
}GameAssets;

#endif // GAME_ASSETS_H_INCLUDED
