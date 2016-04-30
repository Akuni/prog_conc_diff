//
// Created by user on 30/04/16.
//

#include "Semaphore.h"


/*
 * Barriere :
   P(MUTEX)
   Nb_Att++
   SI Nb_Att==N ALORS
      POUR I DE 1 à N-1 FAIRE
         V(ATTENTE)
      FIN POUR

      POUR I DE 1 à N-1 FAIRE
         P(PARTI)
      FIN POUR

      Nb_Att=0
      V(MUTEX)
   SINON
      V(MUTEX)
      P(ATTENTE)
      V(PARTI)
   FIN SI
 */


Semaphore_impl * init_semaphore(unsigned int valeur){
    Semaphore_impl res = (Semaphore_impl) malloc(sizeof(Semaphore_impl));
}

int wait_on_sem(sem_t sem);