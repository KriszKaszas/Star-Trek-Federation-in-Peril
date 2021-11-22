#include "game_engine.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "input_state_interface.h"
#include "debugmalloc.h"

#include "graphics.h"
#include "ui_input.h"
#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"


Uint32 static input_timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

void behavior(){
    int width = 1920, hight = 900;
    InputStateInterface isi = {false, false, false, false, false};
    create_window(width, hight);
    SDL_TimerID id = SDL_AddTimer(1, input_timer, NULL);

    StarMap *sm = starmap_init(width, hight);
    PlayerShip *ps = init_player_ship(width, hight, 100, 1);
    EnemyShip *es = create_enemy_ship(width, 20, 1);
    while(!isi.quit){
        user_input(&isi, id);
        clear_background(sm);
        advance_starmap_frame(sm, width, hight);
        clear_player_ship(ps);
        clear_enemy_ship(es);
        move_player_ship(ps, isi);
        move_enemy_ship(es, width, hight);
        draw_background(sm);
        draw_player_ship(ps);
        draw_enemy_ship(es);
        render_screen();
        random_number_in_range();
    }
    free_starmap(sm);
    free_player_ship(ps);
    free_enemy_ship(es);
    SDL_Quit();
}
