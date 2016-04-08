//
// Created by Nicolas Lecourtois on 03/04/16.
//

#include "BarrierCond.h"

void barrier_cond_init(BarrierCond* barrier, int counter) {
    barrier->remain = counter;
    barrier->threadsAwaiting = counter;
    pthread_mutex_init(&barrier->mutex,NULL);
    pthread_cond_init(&barrier->cond,NULL);
}

int barrier_cond_wait(BarrierCond* barrier) {
    int returnValue = 0;
    // Protection of the counter
    pthread_mutex_lock(&(barrier->mutex));
    // The counter of remaining threads allowed is decremented
    if(--(barrier->remain) == 0) {
        // The counter is reset
        barrier->remain = barrier->threadsAwaiting;
        // Notify all
        pthread_cond_broadcast(&(barrier->cond));

        // Set the return so the caller will know that it's the last thread to call the barrier
        returnValue = PTHREAD_BARRIER_SERIAL_THREAD;
    } else {
        pthread_cond_wait(&(barrier->cond),&(barrier->mutex));
    }
    // The mutex is unlocked
    pthread_mutex_unlock(&(barrier->mutex));
    return returnValue;
}

void barrier_cond_destroy(BarrierCond *barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}