#include "ui_input.h"

#include "input_state_interface.h"
#include "keymap.h"

#include <stdbool.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "debugmalloc.h"

/**
*@brief user_input
*@details A felhaszn�l�t�l �rkez� billenty�parancsokat �rtelmezi, �s egy interface-n kereszt�l adja
�t a program t�bbi r�sz�nek
*@param [in out] isi a j�t�k InputStateInterface-re mutat� pointer. Ezen kereszt�l kommunik�lnak egym�ssal a vez�rl�modulok.
*@param [in] key_map ez a vez�rl� KeyMap interfacen kereszt�l hasonl�tja �ssze a bej�v� billenty�parancsokat a valid vez�rl� gombokkal.
*@param [in] id egy SDL_TimerID t�pus� id�z�t�. Feladata, hogy gener�l egy SDL_USEREVENTet, amennyiben az id�z�t� lej�rt�val nincs be�rkez� esem�ny/parancs
(en�lk�l a vez�rl� blokkoln� a program fut�s�t, nem m�k�dne a h�tt�r anim�ci�, �s semmi nem t�rt�nne, am�g nincs felhaszn�l�i interakci�).
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
