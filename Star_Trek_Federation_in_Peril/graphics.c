#include "graphics.h"
#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"
#include "input_state_interface.h"
#include "phaser.h"
#include "torpedo.h"

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"

static SDL_Window *window;
static SDL_Renderer *renderer;



static void sdl_init(char const *title, int width, int height, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
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

void create_window(int width, int height){
    sdl_init("Star Trek: Federation in Peril", width, height, &window, &renderer);
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


void draw_crosshair(int x_coor, int y_coor){
    lineRGBA(renderer, x_coor-20, y_coor, x_coor+20, y_coor, 255, 50, 50, 255);
    lineRGBA(renderer, x_coor, y_coor-20, x_coor, y_coor+20, 255, 50, 50, 255);
}

void draw_enemy_ships(EnemyArmada *armada){
    for(int i = 0; i < armada->number_of_squadrons; i++){
        EnemySquadronShip *tmp = armada->enemy_armada[i];
        EnemySquadronShip *tmp2 = armada->enemy_armada[i];
        while(tmp != NULL){
            filledCircleRGBA(renderer, tmp->ship.x_coor,
                            tmp->ship.y_coor, 30, 46, 204, 113, 255);
            tmp = tmp->next_ship;
        }
    }
}

void draw_phaser(PhaserBeam *phaser){
    thickLineRGBA(renderer, phaser->beg_x, phaser->beg_y, phaser->end_x, phaser->end_y, 8,
                  phaser->beam_composition.falloff_color.a, phaser->beam_composition.falloff_color.g,
                  phaser->beam_composition.falloff_color.b, phaser->beam_composition.falloff_color.a);
    thickLineRGBA(renderer, phaser->beg_x, phaser->beg_y, phaser->end_x, phaser->end_y, 2,
                  phaser->beam_composition.core_color.a, phaser->beam_composition.core_color.g,
                  phaser->beam_composition.core_color.b, phaser->beam_composition.core_color.a);
}

void draw_torpedo(TorpedoShot *torpedoes){
    TorpedoShot *tmp = torpedoes;
    while(tmp != NULL){
        filledCircleRGBA(renderer, tmp->x_coor, tmp->y_coor, 15,
                         tmp->colors.outter_ring.r, tmp->colors.outter_ring.g, tmp->colors.outter_ring.b, tmp->colors.outter_ring.a);
        filledCircleRGBA(renderer, tmp->x_coor, tmp->y_coor, 10,
                         tmp->colors.inner_ring.r, tmp->colors.inner_ring.g, tmp->colors.inner_ring.b, tmp->colors.inner_ring.a);
        filledCircleRGBA(renderer, tmp->x_coor, tmp->y_coor, 5,
                         tmp->colors.center.r, tmp->colors.center.g, tmp->colors.center.b, tmp->colors.center.a);
        tmp = tmp->next_torpedo;
    }
}

void clear_screen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void render_screen(){
    SDL_RenderPresent(renderer);
}
