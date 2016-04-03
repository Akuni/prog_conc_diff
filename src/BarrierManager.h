//
// Created by user on 03/04/16.
//

#ifndef PROG_CONC_DIFF_BARRIERMANAGER_H
#define PROG_CONC_DIFF_BARRIERMANAGER_H

#include <pthread.h>

typedef enum {
    posix,
    custom_cond,
    custom_semaphore
} implementationChoice;

implementationChoice choice;

void init_barrier(int nb_thread);
int wait_barrier();
void destroy_barrier();


#endif //PROG_CONC_DIFF_BARRIERMANAGER_H
