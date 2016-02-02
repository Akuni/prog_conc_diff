//
// Created by Akuni on 02/02/16.
//

#ifndef PROG_CONC_DIFF_MATRIX_C_H
typedef struct {
    int size;
    int * matrix;
    int middle_index;
    int max_temp_value;
} matrix_representation;



int init_matrix(int, int, matrix_representation *);

void print_matrix(matrix_representation *);

#define PROG_CONC_DIFF_MATRIX_C_H

#endif //PROG_CONC_DIFF_MATRIX_C_H
