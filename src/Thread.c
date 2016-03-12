//
// Created by user on 25/02/16.
//

#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>
#include "Thread.h"
#include "Physics.h"

pthread_barrier_t   barrier_a,  barrier_b;

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
        // swap pointers
        swap_matrix(chunk);
        // wait all thread
        pthread_barrier_wait(&barrier_a);
        // algo from top to bottom
        update_section(chunk, 0);
        // wait all thread
        pthread_barrier_wait(&barrier_b);
        // swap pointers
        swap_matrix(chunk);
        // update center
        set_middle_to_max_temp(chunk->matrix2d);
        // wait all thread
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

/*
void copy_buffer(matrix_chunk * m){
    *//*if(m->idY || m->idX){
        return;
    }*//*
    int i,j;
    for(i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; ++j) {
            *//*m->matrix2d->matrix[i][j] = m->matrix2d->buffer[i][j];
            m->matrix2d->buffer[i][j] = 0 ;*//*
            m->matrix2d->matrix[m->size*m->idX+i][m->size*m->idY+j] = m->matrix2d->buffer[m->size*m->idX+i][m->size*m->idY+j];
            m->matrix2d->buffer[m->size*m->idX+i][m->size*m->idY+j] = 0 ;
        }
    }
}*/

void swap_matrix(matrix_chunk * m){
    if(m->idY || m->idX)
        return;
    float ** temp = m->matrix2d->buffer;
    m->matrix2d->buffer = m->matrix2d->matrix;
    m->matrix2d->matrix = temp;
}

int end_thread(matrix_chunk * m){
    /*free(m->ov_left);
    free(m->ov_bottom);
    free(m->ov_right);
    free(m->ov_top);*/
    return EXIT_SUCCESS;
}