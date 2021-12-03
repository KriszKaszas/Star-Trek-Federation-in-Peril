#include "phaser.h"

Beam create_beam_attributes(BeamColor core, BeamColor falloff){
    Beam *beam_att = malloc(sizeof(Beam));
    beam_att->core_color = core;
    beam_att->falloff_color = falloff;
}

PhaserBeam *phaser_init(Beam beam_att, int x_coor, int y_coor){
    PhaserBeam *phaserbeam = malloc(sizeof(PhaserBeam));
    phaserbeam->beg_x = x_coor;
    phaserbeam->beg_y = y_coor;
    phaserbeam->end_x = x_coor;
    phaserbeam->end_y = y_coor;
    phaserbeam->beam_composition = beam_att;
    return phaserbeam;
}


void free_phaser(PhaserBeam *phaser){
    free(phaser);
}
