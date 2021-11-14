#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

typedef struct enemy_ship{
    int y_coor;
    int x_coor;
    int health;
    int speed;
}EnemyShip;

EnemyShip *create_enemy_ship(int width, int health, int speed);
void move_enemy_ship(EnemyShip *es, int width, int hight);

#endif // ENEMY_SHIP_H
