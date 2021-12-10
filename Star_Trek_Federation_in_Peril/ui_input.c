#include "ui_input.h"

#include "input_state_interface.h"
#include "keymap.h"

#include <stdbool.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "debugmalloc.h"

/**
*@brief user_input
*@details A felhasználótól érkezõ billentyûparancsokat értelmezi, és egy interface-n keresztül adja
át a program többi részének
*@param [in out] isi a játék InputStateInterface-re mutató pointer. Ezen keresztül kommunikálnak egymással a vezérlõmodulok.
*@param [in] key_map ez a vezérlõ KeyMap interfacen keresztül hasonlítja össze a bejövõ billentyûparancsokat a valid vezérlõ gombokkal.
*@param [in] id egy SDL_TimerID típusú idõzítõ. Feladata, hogy generál egy SDL_USEREVENTet, amennyiben az idõzítõ lejártával nincs beérkezõ esemény/parancs
(enélkül a vezérlõ blokkolná a program futását, nem mûködne a háttér animáció, és semmi nem történne, amíg nincs felhasználói interakció).
*@return void
*/

void user_input(InputStateInterface *isi, KeyMap *key_map, SDL_TimerID id){
    SDL_Event event;
    SDL_WaitEvent(&event);
    char *key = SDL_GetKeyName(event.key.keysym.sym);
    switch (event.type) {
        /* felhasznaloi esemeny: ilyeneket general az idozito fuggveny */
        case SDL_USEREVENT:
            break;
        case SDL_KEYUP:
            key = SDL_GetKeyName(event.key.keysym.sym);
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->upkey)){
                isi->up = false;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->downkey)){
                isi->down = false;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->leftkey)){
                isi->left = false;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->rightkey)){
                isi->right = false;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->torpedokey)){
                isi->torpedo_ready = true;
            }
            break;

        case SDL_KEYDOWN:
            key = SDL_GetKeyName(event.key.keysym.sym);
             if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->upkey)){
                isi->up = true;
            printf("%s\n", SDL_GetKeyName(event.key.keysym.sym));
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->downkey)){
                isi->down = true;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->leftkey)){
                isi->left = true;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->rightkey)){
                isi->right = true;
            }
            if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->torpedokey) && isi->torpedo_ready){
                isi->torpedo = true;
                isi->torpedo_ready = false;
            }
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&isi->mouse_position.mouse_x, &isi->mouse_position.mouse_y);

            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT && isi->phaser_ready){
                isi->left_mouse_button = true;
            }

            break;

        case SDL_QUIT:
            isi->quit = true;
            break;
    }
}
