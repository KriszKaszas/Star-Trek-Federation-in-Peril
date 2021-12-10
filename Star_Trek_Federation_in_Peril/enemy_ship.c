#include "enemy_ship.h"

int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

int static *set_squadron_heights(int enemy_spawn_size, int num_of_squadrons, int *squadron_entry_dirs){

    int division = enemy_spawn_size/num_of_squadrons;
    int height = division/2;

    int *squadron_heights = (int*) malloc(num_of_squadrons * sizeof(int));
    for(int i = 0; i < num_of_squadrons; i++){
        if(squadron_entry_dirs[i] == 2){
            squadron_heights[i] = -500;
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

EnemyArmada *init_enemy_armada(LevelDTT *level_dtt, GameAttributes *game_attributes){
    EnemyArmada *enemy_armada = (EnemyArmada*) malloc(sizeof(EnemyArmada));
    EnemySquadronShip **enemy_squadrons = (EnemySquadronShip**) malloc(level_dtt->number_of_squadrons * sizeof(EnemySquadronShip));
    int enemy_spawn_size = (game_attributes->height/3)*2;

    bool *entry_fin_per_sq = (bool*) malloc(level_dtt->number_of_squadrons * sizeof(bool));
    int *squadron_dirs = (int*) malloc(level_dtt->number_of_squadrons * sizeof(int));
    for(int i = 0; i < level_dtt->number_of_squadrons; i++){
        enemy_squadrons[i] = NULL;
        entry_fin_per_sq[i] = false;
    }
    squadron_dirs[0] = 2;
    int decide_dir = random_number_in_range(1, 2);
    squadron_dirs[1] = decide_dir == 1 ? 1 : -1;;
    for(int i = 2; i < level_dtt->number_of_squadrons; i++){
        if(squadron_dirs[i-1] == 1){
            squadron_dirs[i] = -1;
        }
        else{
            squadron_dirs[i] = 1;
        }
    }

    int *squadron_height = set_squadron_heights(enemy_spawn_size, level_dtt->number_of_squadrons, squadron_dirs);
    for(int i = 0; i < level_dtt->number_of_squadrons; i++){

        for(int j = 0; j < level_dtt->ships_per_squadron[i]; j++){
            EnemySquadronShip *enemy_squadron_ship = (EnemySquadronShip*) malloc(sizeof(EnemySquadronShip));
            enemy_squadron_ship->ship = create_enemy_ship(level_dtt->shiptypes_per_squadron[i], squadron_height[i]);
            enemy_squadron_ship->next_ship = enemy_squadrons[i];
            enemy_squadron_ship->prev_ship = NULL;
            if(enemy_squadrons[i] != NULL){
                enemy_squadrons[i]->prev_ship = enemy_squadron_ship;
            }
            enemy_squadrons[i] = enemy_squadron_ship;
        }
    }
    enemy_armada->enemy_armada = enemy_squadrons;
    enemy_armada->number_of_squadrons = level_dtt->number_of_squadrons;
    enemy_armada->squadron_dirs = squadron_dirs;
    enemy_armada->squadron_heights = squadron_height;
    enemy_armada->entry_finished_per_squadron = entry_fin_per_sq;
    enemy_armada->ready_to_move = false;
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
    case -1:
        tmp->ship.x_coor = game_attributes->width+20;
        tmp = tmp->next_ship;
        while(tmp != 0){
            tmp->ship.x_coor = tmp->prev_ship->ship.x_coor + game_attributes->width/squadron_size(squadron);
            tmp = tmp->next_ship;
        }
        break;
    case 2:
        tmp->ship.x_coor = game_attributes->width/squadron_size(squadron)/2;
        tmp = tmp->next_ship;
        while(tmp != 0){
            tmp->ship.x_coor = tmp->prev_ship->ship.x_coor + game_attributes->width/squadron_size(squadron);
            tmp = tmp->next_ship;        }
        break;
    }
}

bool enemy_armada_entry_animation(EnemySquadronShip *squadron, GameAttributes *game_attributes, int dir){
    EnemySquadronShip *tmp = squadron;
    bool is_squadron_entry_finished = false;
    switch (dir){
    case 1:
        if(squadron->ship.x_coor < game_attributes->width-(game_attributes->width/squadron_size(squadron))/2+1){
            while(tmp != 0){
                tmp->ship.x_coor += tmp->ship.speed*3;
                tmp = tmp->next_ship;
            }
        }
        else{
            is_squadron_entry_finished = true;
        }
        break;
    case -1:
        if(squadron->ship.x_coor > game_attributes->width/squadron_size(squadron)/2-1){
            while(tmp!= 0){
                tmp->ship.x_coor -= tmp->ship.speed*3;
                tmp = tmp->next_ship;
             }
        }
        else{
            is_squadron_entry_finished = true;
        }        break;
    case 2:
        if(squadron->ship.y_coor < game_attributes->height/8){
            while(tmp != 0){
                tmp->ship.y_coor +=  tmp->ship.speed;
                tmp = tmp->next_ship;
             }
        }
        else{
            is_squadron_entry_finished = true;
        }
        break;
    }
    return is_squadron_entry_finished;
}

void modify_enemy_dir(EnemyArmada *armada){
    for(int i = 0; i < armada->number_of_squadrons; i++){
        if(armada->squadron_dirs[i] == 2){
            if(i != armada->number_of_squadrons){
                armada->squadron_dirs[i] = armada->squadron_dirs[i+1]*(-1);
            }
            else if(i == armada->number_of_squadrons){
                armada->squadron_dirs[i] = armada->squadron_dirs[i-1]*(-1);
            }
        }
    }
}

int static calculate_enemy_movement_freedom(GameAttributes *game_attributes, EnemySquadronShip *squadron){
    int squadron_size = 0;
    EnemySquadronShip *tmp = squadron;
    while(tmp != NULL){
        squadron_size++;
        tmp = tmp->next_ship;
    }
    return game_attributes->width/squadron_size/3;
}

void manage_enemy_dirs(EnemyArmada *armada, GameAttributes *game_attributes){
    int enemy_movement_freedom;
    for(int i = 0; i < armada->number_of_squadrons; i++){
        enemy_movement_freedom = calculate_enemy_movement_freedom(game_attributes, armada->enemy_armada[i]);
        if(armada->enemy_armada[i]->ship.x_coor > game_attributes->width/2){
            if(armada->squadron_dirs[i] > 0 &&
               armada->enemy_armada[i]->ship.x_coor == game_attributes->width-enemy_movement_freedom){
                   armada->squadron_dirs[i] *= -1;
            }
            else if(armada->squadron_dirs[i] < 0 &&
                    armada->enemy_armada[i]->ship.x_coor == game_attributes->width - (enemy_movement_freedom * 2)){
                        armada->squadron_dirs[i] *= -1;
                    }
        }
        else if(armada->enemy_armada[i]->ship.x_coor < game_attributes->width/2){
                if(armada->squadron_dirs[i] > 0 &&
                   armada->enemy_armada[i]->ship.x_coor == enemy_movement_freedom * 2){
                        armada->squadron_dirs[i] *= -1;
                }
                else if(armada->squadron_dirs[i] < 0 &&
                        armada->enemy_armada[i]->ship.x_coor == enemy_movement_freedom){
                        armada->squadron_dirs[i] *= -1;
                        }
        }
    }
}

void static move_enemy_squadron(EnemySquadronShip *squadron, GameAttributes *game_attributes, int dir){
    EnemySquadronShip *tmp = squadron;
    while(tmp != NULL){
        tmp->ship.x_coor += tmp->ship.speed*dir;
        tmp = tmp->next_ship;
    }
}

void move_enemy_armada(EnemyArmada *armada, GameAttributes *game_attributes){
    for(int i = 0; i < armada->number_of_squadrons; i++){
        move_enemy_squadron(armada->enemy_armada[i], game_attributes, armada->squadron_dirs[i]);
    }
    manage_enemy_dirs(armada, game_attributes);
}

void free_enemy_squadron_ship(EnemySquadronShip **ess){
    EnemySquadronShip *ship = (*ess);
    if((*ess)->prev_ship == NULL && (*ess)->next_ship == NULL){
        (*ess) = NULL;
        free(ship);
    }
    else if((*ess)->prev_ship == NULL){
        if((*ess)->next_ship != NULL){
            (*ess) = ship->next_ship;
        }
        free(ship);
        (*ess)->prev_ship = NULL;

    }
    else if((*ess)->next_ship == NULL){
        if((*ess)->prev_ship != NULL){
            (*ess)->prev_ship->next_ship = NULL;
        }
        free(ship);
    }
    else{
        (*ess)->prev_ship->next_ship = (*ess)->next_ship;
        (*ess)->next_ship->prev_ship = (*ess)->prev_ship;
        free(ship);
    }
}

void free_enemy_squadron(EnemySquadronShip *squadron){
    EnemySquadronShip *ship = squadron;
    while(ship != NULL){
        ship = squadron->next_ship;
        free_enemy_squadron_ship(&squadron);
        squadron = ship;
    }
}

void free_enemy_armada(EnemyArmada *armada){
    for(int i = 0; i < armada->number_of_squadrons; i++){
        free_enemy_squadron(armada->enemy_armada[i]);
    }
    free(armada->squadron_heights);
    free(armada->squadron_dirs);
    free(armada->entry_finished_per_squadron);
    free(armada->enemy_armada);
    free(armada);
}
