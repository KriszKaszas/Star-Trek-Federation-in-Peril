#include "star_map.h"
#include "debugmalloc.h"

int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}


void advance_starmap_frame(StarMap *sm, int width, int hight){
    for(int i = 0; i < sm->length; i++){
        if(sm->stars[i].y_coor < hight + 10){
            sm->stars[i].y_coor += 2;
        }
        else{
            sm->stars[i].y_coor = 0;
            sm->stars[i].x_coor = random_number_in_range(0, width);
        }
    }
}


Star static create_star(int width, int hight){
    int x_coor = random_number_in_range(0, width);
    int y_coor = random_number_in_range(0, hight);
    int radius = random_number_in_range(1, 4);
    Star st = {y_coor, x_coor, radius};
    return st;
}


StarMap *starmap_init(int width, int hight){
    StarColor white = {225, 225, 225, 225};
    int size = width/20;
    Star *stars = (Star*) malloc(size*sizeof(Star));
    for(int i = 0; i < size; i++){
        stars[i] = create_star(width, hight);
    }
    StarMap *sm = (StarMap*) malloc(sizeof(StarMap));
    sm->length = size;
    sm->stars = stars;
    sm->color = white;
    return sm;
}


void free_starmap(StarMap *sm){
    free(sm->stars);
    free(sm);
}

