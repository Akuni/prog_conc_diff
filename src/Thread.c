//
// Created by user on 25/02/16.
//

#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>
#include "Thread.h"
#include "Matrix2D.h"
#include "Physics.h"

pthread_barrier_t   barrier_a,  barrier_b, barrier_c;

void main_posix_thread(void * data){
    matrix_chunk * chunk = (matrix_chunk *) data;

    reset_buffer(chunk->matrix2d);

    // wait all thread
    pthread_barrier_wait(&barrier_a);
    for(int i = 0; i < chunk->exec_number; i++){
        // algo from left to right
        update_section(chunk, 1);
        // wait all thread
        pthread_barrier_wait(&barrier_b);
        copy_buffer(chunk);
        //reset_buffer(chunk->matrix2d);
        pthread_barrier_wait(&barrier_a);
        // algo from top to bottom
        update_section(chunk, 0);
        // wait all thread
        pthread_barrier_wait(&barrier_b);
        copy_buffer(chunk);
        // update center
        set_middle_to_max_temp(chunk->matrix2d);
        pthread_barrier_wait(&barrier_a);

    }
    // fin
    free(chunk);
}


matrix_chunk * init_chunk(matrix_chunk * m , int size, int number, int total_thread, int exec,matrix_2d* matrix2d){
    m->size = size;
    m->matrix2d = matrix2d;
    m->idX = number / total_thread;
    m->idY = number % total_thread;
    m->exec_number = exec;
    return m;
}


int update_section(matrix_chunk * m, int sens){
    diffusion_2d_chunk(m, 4/6.f, 1/6.f, sens);
    return EXIT_SUCCESS;
}


void copy_buffer(matrix_chunk * m){
    if(m->idY || m->idX){
        return;
    }
    int i,j;
    for(i = 0; i < m->matrix2d->size; i++) {
        for (j = 0; j < m->matrix2d->size; ++j) {
            m->matrix2d->matrix[i][j] = m->matrix2d->buffer[i][j];
            m->matrix2d->buffer[i][j] = 0 ;
        }
    }
}


int end_thread(matrix_chunk * m){
    /*free(m->ov_left);
    free(m->ov_bottom);
    free(m->ov_right);
    free(m->ov_top);*/
    return EXIT_SUCCESS;
}