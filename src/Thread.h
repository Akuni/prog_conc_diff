//
// Created by SARROCHE Nicolas on 25/02/16.
//

#ifndef PROG_CONC_DIFF_THREAD_H
#define PROG_CONC_DIFF_THREAD_H
#include <pthread.h>
#include "Matrix2D.h"
#include "Barrier.h"

typedef struct {
    int size;
    matrix_2d* matrix2d;
    int idX, idY;
    int exec_number;

} matrix_chunk;


extern pthread_barrier_t barrier_a; //,  barrier_b;
extern Barrier_impl * barrier_impl;

void main_posix_thread(void * data);
void main_custom_thread(void * data);

matrix_chunk * init_chunk(matrix_chunk * m, int size, int number, int total_thread, int exec, matrix_2d* matrix2d);

int update_section(matrix_chunk * m, int sens);

void swap_matrix(matrix_chunk *m);

int end_thread(matrix_chunk * m);

#endif //PROG_CONC_DIFF_THREAD_H