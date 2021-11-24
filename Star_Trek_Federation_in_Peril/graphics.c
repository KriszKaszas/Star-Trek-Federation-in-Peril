#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
/*
#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"
*/
#include "input_state_interface.h"
#include "debugmalloc.h"
#include "graphics.h"

static SDL_Window *window;
static SDL_Renderer *renderer;



/* ablak letrehozasa */
static void sdl_init(char const *title, int width, int hight, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, hight, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

void create_window(int width, int hight){
    sdl_init("Star Trek: Federation in Peril", width, hight, &window, &renderer);
}

void draw_background(StarMap *sm){
    for(int i = 0; i < sm->length; i++){
        filledCircleRGBA(renderer, sm->stars[i].x_coor, sm->stars[i].y_coor, sm->stars[i].radius,
                         sm->color.r, sm->color.g, sm->color.b, sm->color.a);
    }
}

void draw_player_ship(PlayerShip *ps){
    filledCircleRGBA(renderer, ps->x_coor, ps->y_coor, 30, 218, 223, 225, 255);
}
void clear_screen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void draw_enemy_ship(EnemyShip *es){
    filledCircleRGBA(renderer, es->x_coor, es->y_coor, 30, 46, 204, 113, 255);
}

void render_screen(){
    SDL_RenderPresent(renderer);
}
