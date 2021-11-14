#include "star_map.h"
#include "debugmalloc.h"

int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}


void advance_starmap_frame(StarMap *sm){
    for(int i = 0; i < sm->length; i++){
        if(sm->stars[i].y_coor < 910){
            sm->stars[i].y_coor++;
        }
        else{
            sm->stars[i].y_coor = 0;
            sm->stars[i].x_coor = random_number_in_range(0,1220);
        }
    }
}


Star static create_star(){
    int x_coor = random_number_in_range(0, 1220);
    int y_coor = random_number_in_range(0, 900);
    int radius = random_number_in_range(0, 5);
    Star st = {y_coor, x_coor, radius};
    return st;
}


StarMap *starmap_init(){
    StarColor white = {225, 225, 225, 225};
    Star *stars = (Star*) malloc(20*sizeof(Star));
    for(int i = 0; i < 20; i++){
        stars[i] = create_star();
    }
    StarMap *sm = (StarMap*) malloc(sizeof(StarMap));
    sm->length = 20;
    sm->stars = stars;
    sm->color = white;
    return sm;
}

void free_starmap(StarMap *sm){
    for(int i = 0; i < 20; i++){
        free(sm->stars);
    }
    free(sm);
}

