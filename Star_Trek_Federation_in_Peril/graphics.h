#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "star_map.h"
#include "player_ship.h"
#include "enemy_ship.h"

void create_window(int width, int height);

void draw_background(StarMap *sm);

void clear_background(StarMap *sm);

void draw_player_ship(PlayerShip *ps);

void clear_player_ship(PlayerShip *ps);

void draw_enemy_ship(EnemyArmada *armada);

void clear_enemy_ship(EnemyArmada *armad);

void render_screen();

#endif // GRAPHICS_H_INCLUDED
