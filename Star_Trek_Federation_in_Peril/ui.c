#include "ui.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "keymap_struct.h"
#include "star_map.h"

static SDL_Window *window;
static SDL_Renderer *renderer;



/* ablak letrehozasa */
static void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
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

void create_window(){
    sdl_init("SDL peldaprogram", 1220, 900, &window, &renderer);
}

void draw(Keymap *km) {


        if (km->rajz) {
            if (km->left)
                filledTrigonRGBA(renderer, 50, 100, 150, 50, 150, 150, 0x00, 0xC0, 0x00, 0xFF);
            else
                filledTrigonRGBA(renderer, 50, 100, 150, 50, 150, 150, 0xFF, 0x00, 0x00, 0xFF);
            if (km->right)
                filledTrigonRGBA(renderer, 300, 100, 200, 50, 200, 150, 0x00, 0xC0, 0x00, 0xFF);
            else
                filledTrigonRGBA(renderer, 300, 100, 200, 50, 200, 150, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderPresent(renderer);
            km->rajz = false;
            }
            else
            {
                if(km->quit){
                    SDL_Quit;
                }
            }
}

void draw_background(StarMap *sm){
    for(int i = 0; i < sm->length; i++){
        filledCircleRGBA(renderer, sm->stars[i].x_coor, sm->stars[i].y_coor-1, sm->stars[i].radius,
                         1,1,1,255);
    }
    for(int i = 0; i < sm->length; i++){
        filledCircleRGBA(renderer, sm->stars[i].x_coor, sm->stars[i].y_coor, sm->stars[i].radius,
                         sm->color.r, sm->color.g, sm->color.b, sm->color.a);
    }
    SDL_RenderPresent(renderer);
}
