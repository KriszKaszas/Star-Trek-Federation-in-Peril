#ifndef STAR_MAP_H
#define STAR_MAP_H

typedef struct Star_color{
    int r;
    int g;
    int b;
    int a;
}StarColor;


typedef struct star{
    int y_coor;
    int x_coor;
    int radius;
}Star;


typedef struct Star_map{
    int length;
    Star *stars;
    StarColor color;
}StarMap;


StarMap *starmap_init();


void advance_starmap_frame(StarMap *sm);


void free_starmap(StarMap *sm);

#endif // STAR_MAP_H
