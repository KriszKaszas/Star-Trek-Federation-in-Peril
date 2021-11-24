#ifndef PLAYER_SHIP_H_INCLUDED
#define PLAYER_SHIP_H_INCLUDED

typedef struct playership{
    int y_coor;
    int x_coor;
    int health;
    int speed;
}PlayerShip;

PlayerShip *init_player_ship(int width, int hight, int health, int speed);

void move_player_ship(PlayerShip *ps, InputStateInterface *isi, int width, int hight);

void free_player_ship(PlayerShip *ps);

#endif // PLAYER_SHIP_H_INCLUDED
