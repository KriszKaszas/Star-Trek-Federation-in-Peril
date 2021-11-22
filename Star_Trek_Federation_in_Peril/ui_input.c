#include <input_state_interface.h>
#include "ui_input.h"

#include <stdbool.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


#include "debugmalloc.h"



void user_input(InputStateInterface *isi, SDL_TimerID id){
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch (event.type) {
        /* felhasznaloi esemeny: ilyeneket general az idozito fuggveny */
        case SDL_USEREVENT:
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    isi->up = false;
                    break;
                case
                    SDLK_DOWN: isi->down = false;
                    break;
                case SDLK_LEFT:
                    isi->left = false;
                    break;
                case SDLK_RIGHT:
                    isi->right = false;
                    break;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    isi->up = true;
                    break;
                case
                    SDLK_DOWN: isi->down = true;
                    break;
                case SDLK_LEFT:
                    isi->left = true;
                    break;
                case SDLK_RIGHT:
                    isi->right = true;
                    break;
            }
            break;

        case SDL_QUIT:
            isi->quit = true;
            break;
    }
}
