#ifndef DATA_TRANSFER_TYPES_H_INCLUDED
#define DATA_TRANSFER_TYPES_H_INCLUDED

typedef struct shipavatardtt{

}ShipAvatarDTT;

typedef struct shipdtt{
    int speed;
    int health;
    int damage;
    ///char *avatar_path;
}ShipDTT;

typedef struct leveldtt{
    int number_of_waves;
    int number_of_squadrons;
    ShipDTT **shiptypes_per_squadron;
    int *ships_per_squadron;
}LevelDTT;

#endif // DATA_TRANSFER_TYPES_H_INCLUDED
