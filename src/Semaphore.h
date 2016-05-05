//
// Created by user on 30/04/16.
//

#ifndef PROG_CONC_DIFF_SEMAPHORE_H
#define PROG_CONC_DIFF_SEMAPHORE_H


#include <malloc.h>
#include <semaphore.h>

typedef struct {
    int counter, max_thread;
    sem_t attente_t, mutex_t;
} Semaphore_impl;


Semaphore_impl * init_semaphore(unsigned int valeur);

void wait_on_sem(Semaphore_impl * sem);

void destroy_semaphore(Semaphore_impl * semaphore_impl);

#endif //PROG_CONC_DIFF_SEMAPHORE_H
