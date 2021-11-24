#ifndef ENEMY_SHIP_H_INCLUDED
#define ENEMY_SHIP_H_INCLUDED

typedef struct enemyship{
    int y_coor;
    int x_coor;
    int health;
    int speed;
}EnemyShip;

EnemyShip *create_enemy_ship(int width, int health, int speed);

void move_enemy_ship(EnemyShip *es, int width, int hight);

#endif // ENEMY_SHIP_H_INCLUDED
