/**
 * @authors : Nicolas Sarroche, Nicolas Lecourtois
 */

#include <pthread.h>

#ifndef PROG_CONC_DIFF_MATRIX2D_H
typedef struct {
    int size;
    float** matrix;
    float** buffer;
    int middle_index;
    int half_range;
    float max_temp_value;
} matrix_2d;

typedef struct {
    int startX, startY, endX, endY;
    matrix_2d* matrix;
    int nb_exec;
} section;


int init_matrix_2d(int, float, matrix_2d *);

float** allocate_float_matrix(int size);

void reset_buffer(matrix_2d *);

void reset_matrix(matrix_2d *);

void print_matrix_2d(matrix_2d *);

void print_matrix_2d_quarter(matrix_2d *);

void swapBuffer(matrix_2d* m);

int update_matrix(matrix_2d *, int);

void* diffusion_thread(void* args);

void set_middle_to_max_temp(matrix_2d * m);

void free_matrix(matrix_2d *);
#define PROG_CONC_DIFF_MATRIX2D_H

#endif //PROG_CONC_DIFF_MATRIX2D_H
