#ifndef GAME_ATTRIBUTES_H_INCLUDED
#define GAME_ATTRIBUTES_H_INCLUDED

#include "input_state_interface.h"
#include <SDL.h>

typedef struct gameattributes{
    int width;
    int height;
    InputStateInterface isi;
    SDL_TimerID id;
}GameAttributes;

#endif // GAME_ATTRIBUTES_H_INCLUDED
