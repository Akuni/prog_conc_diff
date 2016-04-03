//
// Created by Nicolas Lecourtois on 03/04/16.
//

#include "BarrierCond.h"
#include <stdio.h>
#include <pthread.h>

void barrier_cond_init(BarrierCond* barrier, int counter) {
    barrier->remain = counter;
    barrier->threadsAwaiting = counter;
    pthread_mutex_init(&barrier->mutex,NULL);
    pthread_cond_init(&barrier->cond,NULL);
}

int barrier_cond_wait(BarrierCond* barrier) {

    // On récupère le mutex (pour le compteur)
    pthread_mutex_lock(&(barrier->mutex));
    // On décrémente le compteur de threads restant et on le compare à 0
    if(--(barrier->remain) == 0) {
        // Reinitialisation du compteur
        barrier->remain = barrier->threadsAwaiting;
        // On notifie tout le monde que le dernier est arrivé
        pthread_cond_broadcast(&(barrier->cond));
        // On débloque le mutex du compteur
        pthread_mutex_unlock(&(barrier->mutex));

        return PTHREAD_BARRIER_SERIAL_THREAD;
    } else {

        if (barrier->remain != 0) {
            pthread_cond_wait(&(barrier->cond),&(barrier->mutex));
        }
        pthread_mutex_unlock(&(barrier->mutex));
        return 0;

    }
    return 0;
}

void barrier_cond_destroy(BarrierCond *barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}