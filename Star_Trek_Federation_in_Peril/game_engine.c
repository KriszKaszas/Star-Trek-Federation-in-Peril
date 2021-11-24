#include "game_engine.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "input_state_interface.h"
#include "keymap.h"
#include "debugmalloc.h"

#include "graphics.h"
#include "ui_input.h"
#include "game_assets.h"
#include "game_attributes.h"
#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"


Uint32 static input_timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

GameAssets static *init_game_assets(width, hight){
    GameAssets *game_assets = (GameAssets*) malloc(sizeof(GameAssets));
    game_assets->star_map = starmap_init(width, hight);
    game_assets->player_ship = init_player_ship(width, hight, 100, 1);
    game_assets->enemy_ship = create_enemy_ship(width, 20, 1);
    return game_assets;
}

GameAttributes static *init_game_attributes(){
    GameAttributes *game_attributes = (GameAttributes*) malloc(sizeof(GameAttributes));
    game_attributes->width = 1900;
    game_attributes->hight = 900;
    game_attributes->isi.up = false;
    game_attributes->isi.down = false;
    game_attributes->isi.left = false;
    game_attributes->isi.right = false;
    game_attributes->isi.quit = false;
    create_window(game_attributes->width, game_attributes->hight);
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

void static draw_graphics(GameAssets *game_assets)
{
    draw_player_ship(game_assets->player_ship);
    draw_background(game_assets->star_map);
    draw_enemy_ship(game_assets->enemy_ship);
}

void static calculate_game_assets(GameAssets *game_assets, GameAttributes *game_attributes){
    move_player_ship(game_assets->player_ship, &game_attributes->isi, game_attributes->width, game_attributes->hight);
    advance_starmap_frame(game_assets->star_map, game_attributes->width, game_attributes->hight);
    move_enemy_ship(game_assets->enemy_ship, game_attributes->width, game_attributes->hight);
}

void static free_assets(GameAssets *game_assets){
    free_starmap(game_assets->star_map);
    free_player_ship(game_assets->player_ship);
    free_enemy_ship(game_assets->enemy_ship);
}

void static free_components(GameAssets *game_assets, GameAttributes *game_attributes){
    free(game_assets);
    free(game_attributes);
}

void static game_loop(GameAssets *game_assets, KeyMap *key_map, GameAttributes *game_attributes){
    while(!game_attributes->isi.quit){
        user_input(&game_attributes->isi, key_map, game_attributes->id);
        clear_graphics(game_assets);
        calculate_game_assets(game_assets, game_attributes);
        draw_graphics(game_assets);
        render_screen();
    }
}

void behavior(){

    GameAttributes *game_attributes = init_game_attributes();
    GameAssets *game_assets = init_game_assets(game_attributes->width, game_attributes->hight);
    KeyMap *key_map = default_keymap_init();
    game_loop(game_assets, key_map, game_attributes);

    free_assets(game_assets);
    free_components(game_assets, game_attributes);
    free(key_map);
    SDL_Quit();
}
