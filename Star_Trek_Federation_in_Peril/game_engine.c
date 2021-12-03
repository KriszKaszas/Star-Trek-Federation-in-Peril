#include "game_engine.h"

#include "input_state_interface.h"
#include "keymap.h"
#include "graphics.h"
#include "ui_input.h"
#include "game_assets.h"
#include "game_attributes.h"
#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "debugmalloc.h"


Uint32 static input_timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

GameAssets static *init_game_assets(GameAttributes *game_attributes){
    GameAssets *game_assets = (GameAssets*) malloc(sizeof(GameAssets));
    game_assets->star_map = starmap_init(game_attributes->width, game_attributes->height);
    game_assets->player_ship = init_player_ship(game_attributes->width, game_attributes->height, 100, 1);
    game_assets->enemy_ships = init_enemy_ships(game_attributes, 10, 1);
    return game_assets;
}

GameAttributes static *init_game_attributes(){
    GameAttributes *game_attributes = (GameAttributes*) malloc(sizeof(GameAttributes));
    MousePosition mouse = {0,0};
    game_attributes->width = 1900;
    game_attributes->height = 900;
    game_attributes->isi.up = false;
    game_attributes->isi.down = false;
    game_attributes->isi.left = false;
    game_attributes->isi.right = false;
    game_attributes->isi.left_mouse_button = false;
    game_attributes->isi.right_mouse_button = false;
    game_attributes->isi.mouse_position = mouse;
    game_attributes->isi.quit = false;
    game_attributes->isi.phaser_ready = true;
    game_attributes->isi.phaser_firing = false;
    create_window(game_attributes->width, game_attributes->height);
    SDL_ShowCursor(SDL_DISABLE);
    game_attributes->id = SDL_AddTimer(2, input_timer, NULL);
    return game_attributes;
}

KeyMap *default_keymap_init(){
    KeyMap *key_map = malloc(sizeof(KeyMap));
    key_map->upkey = "W";
    key_map->downkey = "S";
    key_map->leftkey = "A";
    key_map->rightkey = "D";
    return key_map;
}

void static clear_graphics(GameAssets *game_assets){
    clear_screen();
}

void static draw_graphics(int player_ship_time, GameAssets *game_assets, GameAttributes *game_attributes)
{
    draw_background(game_assets->star_map);
    if(game_attributes->isi.left_mouse_button && game_attributes->isi.phaser_ready && !game_attributes->isi.phaser_firing){
            fire_phaser(&game_attributes->isi, game_assets->player_ship, player_ship_time);
    }
    if(game_attributes->isi.phaser_firing && player_ship_time - game_assets->player_ship->phaser_timer < 1){
        draw_phaser(game_assets->player_ship->phaser_blast);
    }
    if(player_ship_time - game_assets->player_ship->phaser_timer > 1){
        game_attributes->isi.phaser_ready = true;
        game_attributes->isi.phaser_firing = false;
        game_attributes->isi.left_mouse_button  = false;
    }
    draw_enemy_ships(game_assets->enemy_ships);
    draw_player_ship(game_assets->player_ship);
    draw_crosshair(game_attributes->isi.mouse_position.mouse_x, game_attributes->isi.mouse_position.mouse_y);
}

void static calculate_game_assets(GameAssets *game_assets, GameAttributes *game_attributes, int enemy_ship_time){
    int static time = 0;
    move_player_ship(game_assets->player_ship, &game_attributes->isi, game_attributes->width, game_attributes->height);
    advance_starmap_frame(game_assets->star_map, game_attributes->width, game_attributes->height);
    if(enemy_ship_time*2 > time){
        enemy_ships_entry_animation(game_assets->enemy_ships, game_attributes->width, game_attributes->height, 1);
        //move_enemy_ships(game_assets->enemy_ships, game_attributes->width, game_attributes->height);
        time = enemy_ship_time*2;
    }
}

void static free_assets(GameAssets *game_assets){
    free_starmap(game_assets->star_map);
    free_player_ship(game_assets->player_ship);
    free_enemy_ship(game_assets->enemy_ships);
}

void static free_components(GameAssets *game_assets, GameAttributes *game_attributes){
    free(game_assets);
    free(game_attributes);
}

int keep_player_time(){
    return SDL_GetTicks()/50;
}

int keep_enemy_time(){
    return SDL_GetTicks()/20;
}

void static game_loop(GameAssets *game_assets, KeyMap *key_map, GameAttributes *game_attributes){
    int player_ship_time = 0;
    int enemy_ship_time = 0;
    position_enemy_ships(game_assets->enemy_ships, game_attributes, 1);
    while(!game_attributes->isi.quit){
        player_ship_time = keep_player_time();
        enemy_ship_time = keep_enemy_time();
        user_input(&game_attributes->isi, key_map, game_attributes->id);
        clear_graphics(game_assets);
        calculate_game_assets(game_assets, game_attributes, enemy_ship_time);
        draw_graphics(player_ship_time, game_assets, game_attributes);
        render_screen();
    }
}

void behavior(){

    GameAttributes *game_attributes = init_game_attributes();
    GameAssets *game_assets = init_game_assets(game_attributes);
    KeyMap *key_map = default_keymap_init();
    game_loop(game_assets, key_map, game_attributes);

    free_assets(game_assets);
    free_components(game_assets, game_attributes);
    free(key_map);
    SDL_Quit();
}
