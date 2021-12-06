#include "enemy_ship.h"

int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

int static *set_squadron_heights(int enemy_spawn_size, int num_of_squadrons, int *squadron_entry_dirs){

    int division = enemy_spawn_size/num_of_squadrons;
    int height = division/2;

    int *squadron_heights = (int*) malloc(num_of_squadrons * sizeof(int));
    for(int i = 0; i < num_of_squadrons; i++){
        if(squadron_entry_dirs[i] == 3){
            squadron_heights[i] = -100;
            height += division;
        }
        else{
            squadron_heights[i] = height;

            height += division;

        }
    }
    return squadron_heights;
}

EnemyShip create_enemy_ship(ShipDTT *ship_dtt, int y_coor){
    EnemyShip es;
    es.x_coor = -10;
    es.y_coor = y_coor;
    es.speed = ship_dtt->speed;
    es.health = ship_dtt->health;
    es.damage = ship_dtt->damage;
    return es;
}

///TODO: assign squadron_entry_dir, implement squadron_height algo logic
EnemyArmada *init_enemy_armada(LevelDTT *level_dtt, GameAttributes *game_attributes){
    EnemyArmada *enemy_armada = (EnemyArmada*) malloc(sizeof(EnemyArmada));
    EnemySquadronShip **enemy_squadrons = (EnemySquadronShip**) malloc(level_dtt->number_of_squadrons * sizeof(EnemySquadronShip));
    int enemy_spawn_size = (game_attributes->height/3)*2;

    int *squadron_entry_dirs = (int*) malloc(level_dtt->number_of_squadrons * sizeof(int));
    squadron_entry_dirs[0] = 3;
    squadron_entry_dirs[1] = random_number_in_range(1, 2);
    for(int i = 2; i < level_dtt->number_of_squadrons; i++){
        if(squadron_entry_dirs[i-1] == 1){
            squadron_entry_dirs[i] = 2;
        }
        else{
            squadron_entry_dirs[i] = 1;
        }
    }

    int *squadron_height = set_squadron_heights(enemy_spawn_size, level_dtt->number_of_squadrons, squadron_entry_dirs);

    for(int i = 0; i < level_dtt->number_of_squadrons; i++){
        enemy_squadrons[i] = (EnemySquadronShip*) malloc(sizeof(EnemySquadronShip));
        enemy_squadrons[i]->ship = create_enemy_ship(level_dtt->shiptypes_per_squadron[i], squadron_height[i]);
        enemy_squadrons[i]->next_ship = NULL;
        enemy_squadrons[i]->prev_ship = NULL;
    }
    for(int i = 0; i < level_dtt->number_of_squadrons; i++){

        for(int j = 1; j < level_dtt->ships_per_squadron[i]; j++){
            EnemySquadronShip *enemy_squadron_ship = (EnemySquadronShip*) malloc(sizeof(EnemySquadronShip));
            enemy_squadron_ship->ship = create_enemy_ship(level_dtt->shiptypes_per_squadron[i], squadron_height[i]);
            enemy_squadron_ship->next_ship = enemy_squadrons[i];
            enemy_squadrons[i]->prev_ship = enemy_squadron_ship;
            enemy_squadrons[i] = enemy_squadron_ship;
        }
    }
    enemy_armada->enemy_armada = enemy_squadrons;
    enemy_armada->number_of_squadrons = level_dtt->number_of_squadrons;
    enemy_armada->squadron_entry_dirs = squadron_entry_dirs;
    enemy_armada->squadron_heights = squadron_height;
    return enemy_armada;
}

int squadron_size(EnemySquadronShip *squadron){
    EnemySquadronShip *tmp = squadron;
    int ctr = 1;
    while(tmp->next_ship != NULL){
        ctr++;
        tmp = tmp->next_ship;
    }
    return ctr;
}


void position_enemy_armada(EnemySquadronShip *squadron, GameAttributes *game_attributes, int dir){
    EnemySquadronShip *tmp = squadron;
    switch (dir){
    case 1:
        tmp->ship.x_coor = -20;
        tmp = tmp->next_ship;
        while(tmp != 0){
            tmp->ship.x_coor = tmp->prev_ship->ship.x_coor - game_attributes->width/squadron_size(squadron);
            tmp = tmp->next_ship;
        }
        break;
    case 2:
        tmp->ship.x_coor = game_attributes->width+20;
        tmp = tmp->next_ship;
        while(tmp != 0){
            tmp->ship.x_coor = tmp->prev_ship->ship.x_coor + game_attributes->width/squadron_size(squadron);
            tmp = tmp->next_ship;
        }
        break;
    case 3:
        tmp->ship.x_coor = game_attributes->width/squadron_size(squadron)/2;
        tmp = tmp->next_ship;
        while(tmp != 0){
            tmp->ship.x_coor = tmp->prev_ship->ship.x_coor + game_attributes->width/squadron_size(squadron);
            tmp = tmp->next_ship;        }
        break;
    }
}

void enemy_armada_entry_animation(EnemySquadronShip *squadron, GameAttributes *game_attributes, int dir){
    EnemySquadronShip *tmp = squadron;
    switch (dir){
    case 1:
        if(squadron->ship.x_coor < game_attributes->width-(game_attributes->width/squadron_size(squadron))/2+1){
            while(tmp != 0){
                tmp->ship.x_coor += tmp->ship.speed;
                tmp = tmp->next_ship;
            }
        }
        break;
    case 2:
        if(squadron->ship.x_coor > game_attributes->width/squadron_size(squadron)/2-1){
            while(tmp!= 0){
                tmp->ship.x_coor -= tmp->ship.speed;
                tmp = tmp->next_ship;
             }
        }
        break;
    case 3:
        if(squadron->ship.y_coor < game_attributes->height/8){
            while(tmp != 0){
                tmp->ship.y_coor +=  tmp->ship.speed;
                tmp = tmp->next_ship;
             }
        }
        break;
    }

}

void move_enemy_ships(EnemySquadronShip *squadron, GameAttributes *game_attributes, int dir){

}

void free_enemy_squadron_ship(EnemySquadronShip *ess){
    ess->prev_ship->next_ship = ess->next_ship;
    ess->next_ship->prev_ship = ess->prev_ship;
    free(ess);
}

void free_enemy_squadron(EnemySquadronShip *squadron){
    int ctr = 0;
    EnemySquadronShip *tmp = squadron->next_ship;
    while(squadron != NULL){
        tmp = squadron->next_ship;
        free(squadron);
        squadron = tmp;
        ctr++;
    }
}

void free_enemy_armada(EnemyArmada *armada){
    for(int i = 0; i < armada->number_of_squadrons; i++){
        free_enemy_squadron(armada->enemy_armada[i]);
    }
    free(armada->squadron_heights);
    free(armada->squadron_entry_dirs);
    free(armada->enemy_armada);
    free(armada);
}
