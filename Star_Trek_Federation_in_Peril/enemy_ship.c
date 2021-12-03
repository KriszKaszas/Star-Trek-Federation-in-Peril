#include "enemy_ship.h"
#include "debugmalloc.h"


int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

EnemyShip create_enemy_ship(int health, int speed, int x_coor, GameAttributes *game_attributes){
    EnemyShip es;
    es.x_coor = x_coor-100;
    es.y_coor = game_attributes->width/8;
    es.health = health;
    es.speed = speed;
    return es;
}

EnemyShips *init_enemy_ships(GameAttributes *game_attributes, int health, int speed, int dir){
    int size = (game_attributes->width/300);
    EnemyShip *enemy_ship_array= (EnemyShip*) malloc(size*sizeof(EnemyShip));
    enemy_ship_array[0] = create_enemy_ship(speed, health, 20, game_attributes);
    for(int i = 1; i < size; i++){
        enemy_ship_array[i] = create_enemy_ship(speed, health, enemy_ship_array[i-1].x_coor, game_attributes);
    }
    EnemyShips *enemy_armada = (EnemyShips*) malloc(sizeof(EnemyShips));
    enemy_armada->length = size;
    enemy_armada->enemy_ships = enemy_ship_array;
    printf("\n%d\n", enemy_armada->length);
    return enemy_armada;
}

void position_enemy_ships(EnemyShips *es, GameAttributes *game_attributes, int dir){
    switch (dir){
    case 1:
        es->enemy_ships[0].x_coor = -game_attributes->width/es->length;
        for(int i = 1; i < es->length; i++){
            es->enemy_ships[i].x_coor = es->enemy_ships[i-1].x_coor-game_attributes->width/es->length;
        }
        break;
    case 2:
        es->enemy_ships[0].x_coor = game_attributes->width+game_attributes->width/es->length;
        for(int i = 1; i < es->length; i++){
            es->enemy_ships[i].x_coor = es->enemy_ships[i-1].x_coor+game_attributes->width/es->length;
        }
        break;
    case 3:
        es->enemy_ships[0].x_coor = game_attributes->width/es->length/2;
        es->enemy_ships[0].y_coor = 10;
        for(int i = 1; i < es->length; i++){
            es->enemy_ships[i].x_coor = es->enemy_ships[i-1].x_coor+game_attributes->width/es->length;
            es->enemy_ships[i].y_coor = 10;
        }
        break;
    }
}

void enemy_ships_entry_animation(EnemyShips *es, int width, int height, int dir){
    switch (dir){
    case 1:
        if(es->enemy_ships[0].x_coor < width-(width/es->length)/2+1){
            for(int i = 0; i < es->length; i++){
                es->enemy_ships[i].x_coor += es->enemy_ships->speed;
                printf("%d\n", i);
            }
        }
        break;
    case 2:
        if(es->enemy_ships[0].x_coor > width/es->length/2-1){
            for(int i = 0; i < es->length; i++){
                es->enemy_ships[i].x_coor -= es->enemy_ships->speed;
             }
        }
        break;
    case 3:
        if(es->enemy_ships[0].y_coor < width/8){
            for(int i = 0; i < es->length; i++){
                es->enemy_ships[i].y_coor += es->enemy_ships->speed;
             }
        }
        break;
    }

}

void move_enemy_ships(EnemyShips *es, int width, int height, int dir){

}

void free_enemy_ship(EnemyShips *es){
    free(es->enemy_ships);
    free(es);
}
