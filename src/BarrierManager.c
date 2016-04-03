//
// Created by Nicolas Lecourtois on 03/04/16.
//

#include <stdio.h>
#include "BarrierManager.h"


pthread_barrier_t section_barrier;

void init_barrier(int nb_thread){
    switch (choice) {
        case posix:
            pthread_barrier_init(&section_barrier, NULL, nb_thread);
            break;
        case custom_cond:
            break;
        default:
            break;
    }
}

int wait_barrier() {
    switch (choice) {
        case posix:
            return pthread_barrier_wait(&section_barrier);
            break;
        case custom_cond:
            break;
        default:
            break;
    }
}

void destroy_barrier() {
    switch (choice) {
        case posix:
            pthread_barrier_destroy(&section_barrier);
            break;
        case custom_cond:
            break;
        default:
            break;
    }
}