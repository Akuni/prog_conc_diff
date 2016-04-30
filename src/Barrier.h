//
// Created by SARROCHE Nicolas on 01/04/16.
//

#ifndef PROG_CONC_DIFF_BARRIERE_H_H
#define PROG_CONC_DIFF_BARRIERE_H_H

#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int counter, max_thread;
    pthread_cond_t cond_t;
    pthread_mutex_t mutex_t;
} Barrier_impl;

//init barrier
Barrier_impl * init_barrier(int number_of_thread);

// thread wait at the barrier
void wait(Barrier_impl * barrier_impl);

// destroy method ?

#endif //PROG_CONC_DIFF_BARRIERE_H_H
