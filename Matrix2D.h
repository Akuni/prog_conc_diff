//
// Created by user on 02/02/16.
//

#ifndef PROG_CONC_DIFF_MATRIX2D_H
typedef struct {
    int size;
    float ** matrix;
    int middle_index;
    int half_range;
    float max_temp_value;
} matrix_2d;



int init_matrix_2d(int, float, matrix_2d *);

void print_matrix_2d(matrix_2d *);

void print_matrix_2d_quarter(matrix_2d *);

int update_matrix(matrix_2d *, int);

void set_middle_to_max_temp(matrix_2d * m);

void free_matrix(matrix_2d *);
#define PROG_CONC_DIFF_MATRIX2D_H

#endif //PROG_CONC_DIFF_MATRIX2D_H
