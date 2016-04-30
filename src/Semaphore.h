//
// Created by user on 30/04/16.
//

#ifndef PROG_CONC_DIFF_SEMAPHORE_H
#define PROG_CONC_DIFF_SEMAPHORE_H


#include <malloc.h>
#include <semaphore.h>

typedef struct {
    int counter, max_thread;
    sem_t attente_t;
    sem_t mutex_t;
} Semaphore_impl;


Semaphore_impl * init_semaphore(unsigned int valeur);

int wait_on_sem(sem_t sem);

#endif //PROG_CONC_DIFF_SEMAPHORE_H
