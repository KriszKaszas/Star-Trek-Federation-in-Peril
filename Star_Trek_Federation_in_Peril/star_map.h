#ifndef STAR_MAP_H_INCLUDED
#define STAR_MAP_H_INCLUDED

/**
*@brief StarColor
*@details  Ez az adatstruktúra tárolja a háttér csillagának színét. Értékei a csillag RGBA-ban
meghatározott színértékei. Ez az adattároló a függvényhíváskor megadandó paraméterlisták lerövidítését
szolgálja.
*/
typedef struct starcolor{
    int r;  ///< A csillag RGBA piros értéke.
    int g;  ///< A csillag RGBA zöld értéke.
    int b;  ///< A csillag RGBA kék értéke.
    int a;  ///< A csillag RGBA alfa értéke (ez határozza meg a csillag áttetszõségét.
}StarColor;

/**
*@brief Star
*@details Ez az adatstruktúra tárolja a háttér egy csillagát. Értékei a csillag kirajzoláához szükséges koordináták
és sugár. Ez az adattároló a függvényhíváskor megadandó paraméterlisták lerövidítését, illetve az összetartozó adatok egy
helyen tartását szolgálja.
*/
typedef struct star{
    int y_coor; ///< A csillagot jelképzõ kör y koordinátája.
    int x_coor; ///< A csillagot jelképzõ kör x koordinátája.
    int radius; ///< A csillagot jelképzõ kör sugara.
}Star;

/**
*@brief StarMap
*@details Ez az adatstruktúra tárolja a háttér összes csillagát. Értékei a lista hossza, a csillagokat tartalmazó lista,
illetve azok színe. Ez az adattároló a háttér csillagainak könnyû létrehozását, tárolásást és felszabadítását szolgálja.
*/
typedef struct starmap{
    int length;         ///< A lista hossza.
    Star *stars;        ///< A csillagokat tároló lista.
    StarColor color;    ///< A csillagok színét tároló struktúra.
}StarMap;


StarMap *starmap_init(int width, int height);


void advance_starmap_frame(StarMap *sm, int width, int height);


void free_starmap(StarMap *sm);

#endif // STAR_MAP_H_INCLUDED
