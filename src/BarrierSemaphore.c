//
// Created by Nicolas Lecourtois on 26/04/16.
//

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include "BarrierSemaphore.h"

void barrier_semaphore_init(BarrierSemaphore *barrier, int counter) {
    sem_init(&barrier->mutex, NULL, 1);
    sem_init(&barrier->attente, NULL, 0);
    sem_init(&barrier->parti, NULL, 0);
    barrier->nb_att = 0;
    barrier->N = (unsigned) counter;
}

int barrier_semaphore_wait(BarrierSemaphore *barrier) {
    int returnValue = 0;
    //printf("using the right barrier\n");
    sem_wait(&barrier->mutex);
    ++barrier->nb_att;
    if (barrier->nb_att == barrier->N) {
        for (unsigned i = 0; i < barrier->N - 1; ++i) {
            sem_post(&barrier->attente);
        }

        for (unsigned i = 0; i < barrier->N - 1; ++i) {
            sem_wait(&barrier->parti);
        }

        barrier->nb_att = 0;
        sem_post(&barrier->mutex);
        returnValue = PTHREAD_BARRIER_SERIAL_THREAD;
    } else {
        sem_post(&barrier->mutex);
        sem_wait(&barrier->attente);
        sem_post(&barrier->parti);
    }
    return returnValue;
}

void barrier_semaphore_destroy(BarrierSemaphore *barrier) {
    sem_destroy(&barrier->mutex);
    sem_destroy(&barrier->attente);
    sem_destroy(&barrier->parti);
}
