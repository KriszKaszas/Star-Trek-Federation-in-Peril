#ifndef UI_INPUT_H_INCLUDED
#define UI_INPUT_H_INCLUDED

#include "input_state_interface.h"
#include "keymap.h"
#include "SDL_timer.h"

void user_input(InputStateInterface *isi, KeyMap *key_map, SDL_TimerID id);

#endif // UI_INPUT_H_INCLUDED
