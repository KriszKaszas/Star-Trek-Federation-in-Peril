#include "star_map.h"

#include "debugmalloc.h"

/**
*@brief random_number_in_range
*@details egy random sz�mmal t�r vissza egy meghat�rozott intervallumon bel�l. Csak ez a modul h�vhatja
*@param [in] lower az intervallum als� hat�ra.
*@param [in] upper az intervallum fels� hat�ra.
*@return int
*/
int static random_number_in_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

/**
*@brief advance_starmap_frame
*@details a csillagt�rk�pet el�remozd�tja egy kock�val. V�gigmegy a csillagokat tartalmaz� dinamikus list�n, �s mindnek
egyel n�veli az y koordin�t�j�t, amennyiben az nem 10-el nagyobb az ablak magass�g�n�l. Amennyiben enn�l az �rt�kn�l magasabb az adott
csillag y �rt�ke, �gy az y koordin�t�t 0-ra, az x koordin�t�t pedig egy, a k�perny� sz�less�g�ben tal�lhat� random �rt�kre �ll�tja.
*@param [out] sm egy StarMap t�pus� pointer, a j�t�k StarMap t�pus�ban t�rolt csillagok koordin�t�it t�rolja.
*@param [in] width a k�perny� sz�less�ge. Erre a random sz�m gener�l�s�hoz van sz�ks�g.
*@param [in] height a k�perny� magass�ga. Erre a csillag y koordin�t�j�nak ellen�rz�s�hez van sz�ks�g.
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
*@details Ez a f�ggv�ny egy darab csillagot inicializ�l. iv�laszt neki egy random m�retet, �s egy random x �s y
koordin�t�t 0 �s a k�perny� sz�less�ge, valamint 0 �s a k�perny� magass�ga k�z�tt. Az elk�sz�lt csillaggal t�r vissza.
*@param [in] width a k�perny� sz�less�ge. Erre a csillag x koordin�t�j�nak gener�l�s�hoz van sz�ks�g.
*@param [in] height a k�perny� magass�ga. Erre a csillag y koordin�t�j�nak gener�l�s�hoz van sz�ks�g.
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
*@details Ez a f�ggv�ny inicializ�lja a StarMap csillagt�rk�p list�j�t. l�trehoz egy, a csillagok v�rt sz�m�nak megfelel� hossz�s�g� dinamikus t�mb�t,
majd abban elhelyezi a sorban gener�lt csillagokat. Visszat�r�si �rt�ke egy csillagt�rk�p.
*@param [in] width a k�perny� sz�less�ge. Erre a csillagok x koordin�t�j�nak gener�l�s�hoz van sz�ks�g.
*@param [in] height a k�perny� magass�ga. Erre a csillagok y koordin�t�j�nak gener�l�s�hoz van sz�ks�g.
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
*@details Ez a f�ggv�ny a param�terk�nt kapott csillagt�rk�p csillagainak list�j�t, majd mag�t a csillagt�rk�pet szabad�tja fel.
*@param [in] sm a felszabad�tand� csillagt�rk�p pointer.
*@return void
*/
void free_starmap(StarMap *sm){
    free(sm->stars);
    free(sm);
}

