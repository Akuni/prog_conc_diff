/**
 * @authors : Nicolas Sarroche
 */

#include "Matrix2D.h"

#ifndef PROG_CONC_DIFF_PHYSICS_H

int diffusion_2d(matrix_2d *m, float coeff1, float coeff2, int sens);

int diffusion_2d_section(section* s, float coeff1, float coeff2, int sens);

#define PROG_CONC_DIFF_PHYSICS_H

#endif //PROG_CONC_DIFF_PHYSICS_H
