#include "torpedo.h"

TorpedoColors init_torpedo_colors(bool is_enemy_torpedo, bool is_quantum_torpedo){
    TorpedoColors colors;
    if(is_enemy_torpedo){
        ColorData outter_ring = {94, 195, 79, 100};
        colors.outter_ring = outter_ring;
        ColorData inner_ring = {62, 250, 85, 155};
        colors.inner_ring = inner_ring;
        ColorData center = {138, 254, 202, 255};
        colors.center = center;
    }
    else if(is_quantum_torpedo){
        ColorData outter_ring = {94, 195, 79, 100};
        colors.outter_ring = outter_ring;
        ColorData inner_ring = {65, 123, 237, 155};
        colors.inner_ring = inner_ring;
        ColorData center = {255, 255, 255, 255};
        colors.center = center;
    }
    else{
        ColorData outter_ring = {246, 22, 0, 100};
        colors.outter_ring = outter_ring;
        ColorData inner_ring = {246, 22, 0, 155};
        colors.inner_ring = inner_ring;
        ColorData center = {254, 255, 69, 255};
        colors.center = center;
    }
    return colors;
}


TorpedoShot *add_torpedo_shot(TorpedoShot *torpedoes, int damage, int speed, int x_coor, int y_coor, bool is_enemy_torpedo, bool is_quantum_torpedo){

    TorpedoShot *torpedo = (TorpedoShot*) malloc(sizeof(TorpedoShot));
    torpedo->x_coor = x_coor;
    torpedo->y_coor = y_coor;
    torpedo->damage = damage;
    torpedo->speed = speed;
    if(!is_enemy_torpedo && !is_quantum_torpedo){
        torpedo->dir = -1;
    }
    else{
        torpedo->dir = 1;
    }
    torpedo->colors = init_torpedo_colors(is_enemy_torpedo, is_quantum_torpedo);
    torpedo->next_torpedo = torpedoes;
    if(torpedoes != NULL){
        torpedoes->prev_torpedo = torpedo;
    }
    torpedo->prev_torpedo = NULL;
    return torpedo;
}

void remove_torpedo_shot(TorpedoShot **torpedo){
    TorpedoShot *tmp = (*torpedo);
    if((*torpedo)->prev_torpedo == NULL && (*torpedo)->next_torpedo == NULL){
        (*torpedo) = NULL;
        free(tmp);
    }else if((*torpedo)->prev_torpedo == NULL){
        if((*torpedo)->next_torpedo != NULL){
            (*torpedo) = tmp->next_torpedo;
        }
        free(tmp);
        (*torpedo)->prev_torpedo = NULL;
    }
    else if((*torpedo)->next_torpedo == NULL){
        if((*torpedo)->prev_torpedo != NULL){
            (*torpedo)->prev_torpedo->next_torpedo = NULL;
        }
        free(tmp);

    }
    else{
        (*torpedo)->prev_torpedo->next_torpedo = (*torpedo)->next_torpedo;
        (*torpedo)->next_torpedo->prev_torpedo = (*torpedo)->prev_torpedo;
        free((*torpedo));
    }
}


void move_torpedoes(TorpedoShot **torpedo, GameAttributes *game_attributes){
    TorpedoShot *tmp = (*torpedo);
    while(tmp != NULL){
        if((*torpedo)->y_coor > game_attributes->height + 10 || (*torpedo)->y_coor < - 10){
                tmp = (*torpedo)->next_torpedo;
                remove_torpedo_shot(torpedo);
                (*torpedo) = tmp;
        }
        else{
        tmp->y_coor += tmp->dir;
        tmp = tmp->next_torpedo;
        }
    }
}

void free_torpedoes(TorpedoShot *torpedoes){
    TorpedoShot *tmp = torpedoes;
    while(tmp != NULL){
        tmp = torpedoes->next_torpedo;
        remove_torpedo_shot(&torpedoes);
        torpedoes = tmp;
    }
}
