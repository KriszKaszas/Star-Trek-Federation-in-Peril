#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

typedef struct player_ship{
    int y_coor;
    int x_coor;
    int health;
    int speed;
}PlayerShip;

PlayerShip *init_player_ship(int width, int hight, int health, int speed);

void move_player_ship(PlayerShip *ps, InputStateInterface *isi);

void free_player_ship(PlayerShip *ps);

#endif // PLAYER_SHIP_H
