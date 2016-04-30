//
// Created by LECOURTOIS Nicolas & SARROCHE Nicolas on 02/02/16.
//

#include "Matrix2D.h"
#include "Thread.h"

#ifndef PROG_CONC_DIFF_PHYSICS_H


int diffusion_2d(matrix_2d *m, float coeff1, float coeff2, int sens);

int diffusion_2d_chunk(matrix_chunk * m, float coeff1, float coeff2, int sens);



#define PROG_CONC_DIFF_PHYSICS_H

#endif //PROG_CONC_DIFF_PHYSICS_H
