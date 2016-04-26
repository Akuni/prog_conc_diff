//
// Created by Nicolas Lecourtois on 03/04/16.
//

#ifndef PROG_CONC_DIFF_BARRIERCOND_H
#define PROG_CONC_DIFF_BARRIERCOND_H

#include <pthread.h>

// Condition variable version
typedef struct {
    int remain;
    int threadsAwaiting;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} BarrierCond;

void barrier_cond_init(BarrierCond* barrier, int counter);

int barrier_cond_wait(BarrierCond * barrier);

void barrier_cond_destroy(BarrierCond *barrier);

#endif //PROG_CONC_DIFF_BARRIERCOND_H
