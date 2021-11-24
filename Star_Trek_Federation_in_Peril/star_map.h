#ifndef STAR_MAP_H_INCLUDED
#define STAR_MAP_H_INCLUDED

typedef struct starcolor{
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


typedef struct starmap{
    int length;
    Star *stars;
    StarColor color;
}StarMap;


StarMap *starmap_init(int width, int hight);


void advance_starmap_frame(StarMap *sm, int width, int hight);


void free_starmap(StarMap *sm);

#endif // STAR_MAP_H_INCLUDED
