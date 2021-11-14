#include "ui_input.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


#include "keymap_struct.h"



void user_input(Keymap *km, SDL_TimerID id){
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch (event.type) {
        /* felhasznaloi esemeny: ilyeneket general az idozito fuggveny */
        case SDL_USEREVENT:
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT: km->left = false; km->rajz = true; break;
                case SDLK_RIGHT: km->right = false; km->rajz = true; break;
                case SDLK_ESCAPE: km->quit = true; break;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT: km->left = true; km->rajz = true; break;
                case SDLK_RIGHT: km->right = true; km->rajz = true; break;
            }
            break;

        case SDL_QUIT:
            km->quit = true;
            break;
    }
}
