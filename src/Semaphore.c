//
// Created by user on 30/04/16.
//

#include <stdlib.h>
#include "Semaphore.h"


/**
 *
 */
Semaphore_impl * init_semaphore(unsigned int valeur){
    Semaphore_impl * res = (Semaphore_impl *) malloc(sizeof(Semaphore_impl));
    res->max_thread = valeur;
    res->counter = 0;
    // retour toujours different de 0
    // et pourtant fonctionne ...
    sem_init(&(res->mutex_t), 0, 1);
    sem_init(&(res->attente_t), 0, 0);
    return res;
}

/*
 * P(MUTEX)
   Nb_Att++
   SI Nb_Att==N ALORS
      POUR I DE 1 à N-1 FAIRE
         V(ATTENTE)
      FIN POUR
      Nb_Att=0
      V(MUTEX)
   SINON
      V(MUTEX)
      P(ATTENTE)
   FIN SI
 */
void wait_on_sem(Semaphore_impl * sem){
    sem_wait(&sem->mutex_t);
    sem->counter++;
    if(sem->counter == sem->max_thread){
        for(int i = 0; i < sem->max_thread; i++){
            sem_post(&sem->attente_t);
        }
        sem->counter = 0;
        sem_post(&sem->mutex_t);

    } else {
        sem_post(&sem->mutex_t);
        sem_wait(&sem->attente_t);
    }
}

void destroy_semaphore(Semaphore_impl * semaphore_impl){
    //free(&semaphore_impl->mutex_t);
    //free(&semaphore_impl->attente_t);
    free(semaphore_impl);
}