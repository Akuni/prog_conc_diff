//
// Created by Nicolas Lecourtois on 26/04/16.
//

#ifndef PROG_CONC_DIFF_BARRIERSEMAPHORE_H
#define PROG_CONC_DIFF_BARRIERSEMAPHORE_H

#include <semaphore.h>

// Semaphore barrier version
typedef struct {
    sem_t mutex;
    sem_t attente;
    sem_t parti;
    unsigned nb_att;
    unsigned N; // number of tasks that have to be blocked before the barrier opens
} BarrierSemaphore;


void barrier_semaphore_init(BarrierSemaphore* barrier, int counter);

int barrier_semaphore_wait(BarrierSemaphore * barrier);

void barrier_semaphore_destroy(BarrierSemaphore *barrier);

#endif //PROG_CONC_DIFF_BARRIERSEMAPHORE_H
