//
// Created by user on 30/03/16.
//

#ifndef PROG_CONC_DIFF_BARRIERE_H_H
#define PROG_CONC_DIFF_BARRIERE_H_H


#include <bits/pthreadtypes.h>
#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int counter, max_thread;
    pthread_cond_t cond_t;
    pthread_mutex_t mutex_t;
    // count
    // limit
    // p_thread_cond
    // p_thread_mutex
} Barrier_impl;


//init easy
Barrier_impl * init_barrier(int number_of_thread){
    Barrier_impl * barrier_impl;
    barrier_impl = malloc(sizeof(Barrier_impl));
    if(barrier_impl == NULL){
        perror("Couldn't allocate custom barrier ");
        exit(EXIT_FAILURE);
    }
    barrier_impl->counter = 0;
    barrier_impl->max_thread = number_of_thread;


    pthread_cond_init(&barrier_impl->cond_t, NULL);
    pthread_mutex_init(&barrier_impl->mutex_t, NULL);

    printf("%d, %d, %d, %d", barrier_impl->counter, barrier_impl->max_thread, barrier_impl-> cond_t, barrier_impl->mutex_t);
    return barrier_impl;
}

void wait(Barrier_impl * barrier_impl){
    if(!pthread_mutex_lock(&barrier_impl->mutex_t)){
        perror("Couldn't lock custom mutex !");
        exit(EXIT_FAILURE);
    }
    // one more thread waiting
    barrier_impl->counter++;

    // limit reached
    if(barrier_impl->counter == barrier_impl->max_thread){
        pthread_cond_broadcast(&barrier_impl->cond_t);
    }else {
        // wait for other thread
        pthread_cond_wait(&barrier_impl->cond_t, &barrier_impl->mutex_t);
    }
    if(!pthread_mutex_unlock(&barrier_impl->mutex_t)){
        perror("Couldn't unlock custom mutex !");
        exit(EXIT_FAILURE);
    }
}
//wait
// lock
// incr
// si limit -> 0 & broadcast (&cond) -> loop
// sinon wait(&cond, &mutex)
// unlock

// destroy ?
#endif //PROG_CONC_DIFF_BARRIERE_H_H
