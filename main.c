/*
 * main.c
 * 
 * Copyright 2016 Akuni <user@Axxx>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

#include "Matrix.h"
#include "Physics.h"
#include "Matrix2D.h"

int main(int argc, char **argv) {
    matrix_representation m;
    int status = init_matrix(7, 256, &m);
    print_matrix(&m);
/*    int i;
    for (i = 0; i < 10; i++) {
        diffusion(&m, 4 / 6.f, 1 / 6.f);
        print_matrix(&m);
    }*/

    matrix_2d matrix2d;
    int status2 = init_matrix_2d(12,256, &matrix2d);
    print_matrix_2d(&matrix2d);

    update_matrix(&matrix2d);
}


