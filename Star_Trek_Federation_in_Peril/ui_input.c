#include "input_state_interface.h"
#include "ui_input.h"
#include "keymap.h"

#include <stdbool.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


#include "debugmalloc.h"



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

            /*
            if(event.key.keysym.sym == 'g')
                printf("G was pressed\n");
            */
            //char *key = SDL_GetKeyName(event.key.keysym.sym);
            printf("KeyUp %s\n", key);

            printf(isi->up ? "W: true\n" : "W: false\n");
            printf(isi->down ? "S: true\n" : "S: false\n");
            printf(isi->left ? "A: true\n" : "A: false\n");
            printf(isi->right ? "D: true\n" : "D: false\n");
            /*
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->upkey) ? "W: true\n" : "W: false\n");
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->downkey) ? "S: true\n" : "S: false\n");
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->leftkey) ? "A: true\n" : "A: false\n");
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->rightkey) ? "D: true\n" : "D: false\n");
            */
            break;

        case SDL_KEYDOWN:
            key = SDL_GetKeyName(event.key.keysym.sym);
             if(event.key.keysym.sym == SDL_GetKeyFromName(key_map->upkey)){
                isi->up = true;
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
            printf("KeyDown %s\n", key);

            printf(isi->up ? "W: true\n" : "W: false\n");
            printf(isi->down ? "S: true\n" : "S: false\n");
            printf(isi->left ? "A: true\n" : "A: false\n");
            printf(isi->right ? "D: true\n" : "D: false\n");

            /*
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->upkey) ? "W: true\n" : "W: false\n");
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->downkey) ? "S: true\n" : "S: false\n");
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->leftkey) ? "A: true\n" : "A: false\n");
            printf(event.key.keysym.sym == SDL_GetKeyFromName(key_map->rightkey) ? "D: true\n" : "D: false\n");
            */
            break;

        case SDL_QUIT:
            isi->quit = true;
            break;
    }
}
