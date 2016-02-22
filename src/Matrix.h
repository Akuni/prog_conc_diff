/**
 * @authors : Nicolas Sarroche
 */


#ifndef PROG_CONC_DIFF_MATRIX_C_H
typedef struct {
    int size;
    float * matrix;
    int middle_index;
    float max_temp_value;
} matrix_representation;



int init_matrix(int, float, matrix_representation *);

void print_matrix(matrix_representation *);

#define PROG_CONC_DIFF_MATRIX_C_H

#endif //PROG_CONC_DIFF_MATRIX_C_H
