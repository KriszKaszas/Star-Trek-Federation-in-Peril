#include "star_map.h"

#include "debugmalloc.h"

/**
*@brief random_number_in_range
*@details egy random számmal tér vissza egy meghatározott intervallumon belül. Csak ez a modul hívhatja
*@param [in] lower az intervallum alsó határa.
*@param [in] upper az intervallum felsõ határa.
*@return int
*/
int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

/**
*@brief advance_starmap_frame
*@details a csillagtérképet elõremozdítja egy kockával. Végigmegy a csillagokat tartalmazó dinamikus listán, és mindnek
egyel növeli az y koordinátáját, amennyiben az nem 10-el nagyobb az ablak magasságánál. Amennyiben ennél az értéknél magasabb az adott
csillag y értéke, úgy az y koordinátát 0-ra, az x koordinátát pedig egy, a képernyõ szélességében található random értékre állítja.
*@param [out] sm egy StarMap típusú pointer, a játék StarMap típusában tárolt csillagok koordinátáit tárolja.
*@param [in] width a képernyõ szélessége. Erre a random szám generálásához van szükség.
*@param [in] height a képernyõ magassága. Erre a csillag y koordinátájának ellenõrzéséhez van szükség.
*@return void
*/
void advance_starmap_frame(StarMap *sm, int width, int height){
    for(int i = 0; i < sm->length; i++){
        if(sm->stars[i].y_coor < height + 10){
            sm->stars[i].y_coor += 2;
        }
        else{
            sm->stars[i].y_coor = 0;
            sm->stars[i].x_coor = random_number_in_range(0, width);
        }
    }
}

/**
*@brief create_star
*@details Ez a függvény egy darab csillagot inicializál. iválaszt neki egy random méretet, és egy random x és y
koordinátát 0 és a képernyõ szélessége, valamint 0 és a képernyõ magassága között. Az elkészült csillaggal tér vissza.
*@param [in] width a képernyõ szélessége. Erre a csillag x koordinátájának generálásához van szükség.
*@param [in] height a képernyõ magassága. Erre a csillag y koordinátájának generálásához van szükség.
*@return Star
*/
Star static create_star(int width, int height){
    int x_coor = random_number_in_range(0, width);
    int y_coor = random_number_in_range(0, height);
    int radius = random_number_in_range(1, 4);
    Star st = {y_coor, x_coor, radius};
    return st;
}

/**
*@brief starmap_init
*@details Ez a függvény inicializálja a StarMap csillagtérkép listáját. létrehoz egy, a csillagok várt számának megfelelõ hosszúságú dinamikus tömböt,
majd abban elhelyezi a sorban generált csillagokat. Visszatérési értéke egy csillagtérkép.
*@param [in] width a képernyõ szélessége. Erre a csillagok x koordinátájának generálásához van szükség.
*@param [in] height a képernyõ magassága. Erre a csillagok y koordinátájának generálásához van szükség.
*@return StarMap
*/
StarMap *starmap_init(int width, int height){
    StarColor white = {225, 225, 225, 225};
    int size = width/20;
    Star *stars = (Star*) malloc(size*sizeof(Star));
    for(int i = 0; i < size; i++){
        stars[i] = create_star(width, height);
    }
    StarMap *sm = (StarMap*) malloc(sizeof(StarMap));
    sm->length = size;
    sm->stars = stars;
    sm->color = white;
    return sm;
}

/**
*@brief free_starmap
*@details Ez a függvény a paraméterként kapott csillagtérkép csillagainak listáját, majd magát a csillagtérképet szabadítja fel.
*@param [in] sm a felszabadítandó csillagtérkép pointer.
*@return void
*/
void free_starmap(StarMap *sm){
    free(sm->stars);
    free(sm);
}

