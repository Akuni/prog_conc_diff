//
// Created by Nicolas Lecourtois on 03/04/16.
//

#include <stdio.h>
#include "BarrierManager.h"
#include "BarrierCond.h"
#include "BarrierSemaphore.h"


pthread_barrier_t section_barrier;
BarrierCond section_barrier_cond;
BarrierSemaphore barrier_semaphore;

void init_barrier(int nb_thread){
    switch (choice) {
        case posix:
            pthread_barrier_init(&section_barrier, NULL, nb_thread);
            break;
        case custom_cond:
            barrier_cond_init(&section_barrier_cond, nb_thread);
            break;
        default:
            barrier_semaphore_init(&barrier_semaphore, nb_thread);
            break;
    }
}

int wait_barrier() {
    switch (choice) {
        case posix:
            return pthread_barrier_wait(&section_barrier);
            break;
        case custom_cond:
            return barrier_cond_wait(&section_barrier_cond);
            break;
        default:
            return barrier_semaphore_wait(&barrier_semaphore);
            break;
    }
}

void destroy_barrier() {
    switch (choice) {
        case posix:
            pthread_barrier_destroy(&section_barrier);
            break;
        case custom_cond:
            barrier_cond_destroy(&section_barrier_cond);
            break;
        default:
            barrier_semaphore_destroy(&barrier_semaphore);
            break;
    }
}