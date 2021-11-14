#include "game_engine.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "keymap_struct.h"
#include "debugmalloc.h"

#include "ui.h"
#include "ui_input.h"
#include "star_map.h"


Uint32 static input_timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

void behavior()
{
    Keymap km = {false, false, false, true};
    create_window();
    SDL_TimerID id = SDL_AddTimer(1, input_timer, NULL);
    StarMap *sm = starmap_init();
    while(!km.quit){
        //draw();
        draw_background(sm);
        advance_starmap_frame(sm);
        user_input(&km, id);
    }
    free_starmap(sm);
    SDL_Quit();
}
