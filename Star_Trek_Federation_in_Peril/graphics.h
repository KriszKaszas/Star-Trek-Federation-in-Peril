#ifndef GRAPHICS_H
#define GRAPHICS_H

void create_window(int width, int hight);

void draw_background(StarMap *sm);

void clear_background(StarMap *sm);

void draw_player_ship(PlayerShip *ps);

void clear_player_ship(PlayerShip *ps);

void draw_enemy_ship(EnemyShip *es);

void clear_enemy_ship(EnemyShip *es);

void render_screen();

#endif // GRAPHICS_H
