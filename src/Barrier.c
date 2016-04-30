//
// Created by SARROCHE Nicolas on 01/04/16.
//

#include "Barrier.h"


Barrier_impl * init_barrier(int number_of_thread){
    // init the barrier
    Barrier_impl * barrier_impl;
    //allocate memory
    barrier_impl = malloc(sizeof(Barrier_impl));
    // check status
    if(barrier_impl == NULL){
        perror("Couldn't allocate custom barrier ");
        exit(EXIT_FAILURE);
    }

    // init variables
    barrier_impl->counter = 0;
    barrier_impl->max_thread = number_of_thread;

    // init internal barrier condition
    pthread_cond_init(&barrier_impl->cond_t, NULL);
    // init internal mutex
    pthread_mutex_init(&barrier_impl->mutex_t, NULL);

    return barrier_impl;
}

void wait(Barrier_impl * barrier_impl){

    if(pthread_mutex_lock(&barrier_impl->mutex_t)){
        perror("Couldn't lock custom mutex !");
        exit(EXIT_FAILURE);
    }
    // one more thread waiting
    barrier_impl->counter++;

    // limit reached
    if(barrier_impl->counter == barrier_impl->max_thread){
        barrier_impl->counter = 0;
        pthread_cond_broadcast(&barrier_impl->cond_t);
    }else {
        // wait for other thread
        pthread_cond_wait(&barrier_impl->cond_t, &barrier_impl->mutex_t);
    }
    if(pthread_mutex_unlock(&barrier_impl->mutex_t)){
        perror("Couldn't unlock custom mutex !");
        exit(EXIT_FAILURE);
    }
}