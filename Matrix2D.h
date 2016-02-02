//
// Created by user on 02/02/16.
//

#ifndef PROG_CONC_DIFF_MATRIX2D_H
typedef struct {
    int size;
    int * array;
    int ** matrix;
    int middle_index;
    int max_temp_value;
} matrix_2d;



int init_matrix(int, int, matrix_2d *);

void print_matrix(matrix_2d *);
#define PROG_CONC_DIFF_MATRIX2D_H

#endif //PROG_CONC_DIFF_MATRIX2D_H
