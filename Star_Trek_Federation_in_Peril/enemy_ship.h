#ifndef ENEMY_SHIP_H_INCLUDED
#define ENEMY_SHIP_H_INCLUDED

#include "debugmalloc.h"
#include "game_attributes.h"

typedef struct enemyship{
    int y_coor;
    int x_coor;
    int health;
    int speed;
}EnemyShip;

typedef struct enemyships{
    int length;
    EnemyShip *enemy_ships;
}EnemyShips;

EnemyShip create_enemy_ship(int health, int speed, int x_coor, GameAttributes *game_attributes);

void move_enemy_ship(EnemyShip *es, int width, int height);

#endif // ENEMY_SHIP_H_INCLUDED
