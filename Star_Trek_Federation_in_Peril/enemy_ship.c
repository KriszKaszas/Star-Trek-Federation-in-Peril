#include "enemy_ship.h"
#include "debugmalloc.h"

int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

EnemyShip *create_enemy_ship(int width, int health, int speed){
    EnemyShip *es = (EnemyShip*) malloc(sizeof(EnemyShip));
    es->x_coor = random_number_in_range(0, width);
    es->y_coor = -10;
    es->health = health;
    es->speed = speed;
    return es;
}

void move_enemy_ship(EnemyShip *es, int width, int hight){
    if(es->y_coor < hight+10){
        es->y_coor += es->speed;
    }
    else{
        es->y_coor = 0;
        es->x_coor = random_number_in_range(0, width);
    }
}

void free_enemy_ship(EnemyShip *es){
    free(es);
}
