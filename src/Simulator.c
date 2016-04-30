//
// Created by LECOURTOIS Nicolas & SARROCHE Nicolas on 20/02/16.
//

#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include "Matrix2D.h"
#include "Simulator.h"
#include "Thread.h"

pthread_barrier_t   barrier_a;
Barrier_impl * barrier_impl;

exec_stats compute_average(exec_stats stats_array[10], int array_length);

void init_stats(exec_stats * stats) {
    stats->execution_time_cpu = 0;
    stats->execution_time_user = 0;
}

void print_stats(exec_stats * stats) {
    printf("Execution statistics\n");
    printf(" Cpu exec time : %lf\n", stats->execution_time_cpu);
    printf(" User exec time : %lf\n", stats->execution_time_cpu);
}


/**
 * Run the simulation once
 * If execution stats are ordered, return them.
 */
exec_stats run_one_iterative(matrix_2d *matrix2d, int measure_cpu, int measure_usr, int execution_number) {
    exec_stats stats;
    init_stats(&stats);
    // if -m, start chrono
    clock_t clockBegin = 0;
    time_t timeBegin = 0;
    if (measure_cpu) {
        clockBegin = clock();
    }
    if (measure_usr) {
        timeBegin = time(NULL);
    }

    // init the 2D matrix
    reset_matrix(matrix2d);
    update_matrix(matrix2d, execution_number);

    // if -m, stop the chrono
    if (measure_cpu) {
        stats.execution_time_cpu = (double) (clock() - clockBegin) / CLOCKS_PER_SEC;
    }
    if (measure_usr) {
        stats.execution_time_user = time(NULL) - timeBegin;
    }
    return stats;
}

/**
 * Run the simulation once or several times depending on whether we need stats or not.
 */
exec_stats runIterative(matrix_2d *matrix2d, int measure_cpu, int measure_usr, int execution_number) {
    exec_stats stats_array[NB_ITERATION];
    int flag_must_make_average = measure_cpu || measure_usr;
    int nb_iteration = flag_must_make_average ? NB_ITERATION : 1;

    printf("Iterative : \n");
    for (unsigned i = 0; i < nb_iteration; ++i) {
        stats_array[i] = run_one_iterative(matrix2d, measure_cpu, measure_usr, execution_number);

        printf("%d iteration -> %.4fs(cpu), %.4fs (user)\n", (i+1), stats_array[i].execution_time_cpu, stats_array[i].execution_time_user);

    }

    exec_stats stats = compute_average(stats_array, nb_iteration);

    return stats;
}

/**
 * Compute the average execution stats
 */
exec_stats compute_average(exec_stats stats_array[], int array_length) {
    exec_stats stats;
    // If we don't have enough stats to ignore the first and the last, we chose the first value
    if (1 < array_length && array_length < 3) {
        stats = stats_array[0];
    } else {
        // If we have enough data to compute an average
        init_stats(&stats);

        // The extremes are not taken into account to compute the average
        for (unsigned i = 1; i < array_length-1; ++i) {
            stats.execution_time_cpu += stats_array[i].execution_time_cpu;
            stats.execution_time_user += stats_array[i].execution_time_user;
        }
        stats.execution_time_cpu /= (array_length - 2);
        stats.execution_time_user /= (array_length - 2);
    }
    return stats;
}


exec_stats runThreadPosix(matrix_2d * matrix2d, int number, int cpu, int user, int execution_number) {
    exec_stats stats_array[NB_ITERATION];
    int flag_must_make_average = cpu || user;
    int nb_iteration = flag_must_make_average ? NB_ITERATION : 1;

    printf("Posix : \n");
    for (unsigned i = 0; i < nb_iteration; ++i) {
        reset_matrix(matrix2d);
        reset_buffer(matrix2d);
        stats_array[i] = run_one_posix(matrix2d, number, cpu, user, execution_number);
        //printf("%d iteration -> %.4fs(cpu), %.4fs (user)\n", (i+1), stats_array[i].execution_time_cpu, stats_array[i].execution_time_user);
    }

    exec_stats stats = compute_average(stats_array, nb_iteration);

    return stats;
}


exec_stats run_one_posix(matrix_2d *matrix2d, int thread_number, int measure_cpu, int measure_usr, int execution_number) {

    exec_stats stats;
    init_stats(&stats);
    // if -m, start chrono
    clock_t clockBegin = 0;
    time_t timeBegin = 0;
    if (measure_cpu) {
        clockBegin = clock();
    }
    if (measure_usr) {
        timeBegin = time(NULL);
    }

    // reset buffer
    reset_buffer(matrix2d);

    // total thread number
    unsigned thread_total = (unsigned) 1 << (thread_number);
    // number of thread per "line"
    int thread_by_line = (int) sqrtl((long)thread_total);
    // block size of a thread
    int size = matrix2d->size / thread_by_line;

    if(!size){
        fprintf(stderr, "error: With %d threads, the size is %d, which is impossible ! \n", thread_total, size );
        return stats;
        //exit(0);
    }

    // init barriers
    pthread_barrier_init(&barrier_a,NULL, thread_total);

    // init thread chunks
    matrix_chunk ** array_chunk = (matrix_chunk**) malloc(sizeof(matrix_chunk)* thread_total);
    if(array_chunk == NULL){
        fprintf(stderr, "error: Cannot allocate chunk array !\n");
        exit(0);
    }

    for(int i = 0; i < thread_total ;  i++){
        array_chunk[i] = malloc(sizeof(matrix_chunk));
        if(array_chunk[i] == NULL){
            fprintf(stderr, "error: Cannot create chunk # %d\n", i);
            exit(0);
        }
        array_chunk[i] = init_chunk(array_chunk[i], size, i, thread_by_line, execution_number, matrix2d);
    }

    // init threads
    pthread_t  array[thread_total];
    for(int i = 0; i < thread_total; i++){
        if(array_chunk[i] == NULL){
            fprintf(stderr, "error: Cannot create chunk # %d\n", i);
            exit(0);
        }

        if (pthread_create(&array[i], NULL, (void*) main_posix_thread, array_chunk[i]) != 0) {
            fprintf(stderr, "error: Cannot create thread # %d\n", i);
            break;
        }
    }

    // join threads
    void * retvals[thread_total];
    for (int i = 0; i < thread_total; ++i) {
        if (pthread_join(array[i], &retvals[i]) != 0) {
            fprintf(stderr, "error: Cannot join thread # %d\n", i);
        }
    }

    // if -m, stop the chrono
    if (measure_cpu) {
        stats.execution_time_cpu = (double) (clock() - clockBegin) / CLOCKS_PER_SEC;
    }
    if (measure_usr) {
        stats.execution_time_user = time(NULL) - timeBegin;
    }
    return stats;
}


exec_stats runCustomBarrier(matrix_2d * matrix2d, int number, int cpu, int user, int execution_number) {
    exec_stats stats_array[NB_ITERATION];
    int flag_must_make_average = cpu || user;
    int nb_iteration = flag_must_make_average ? NB_ITERATION : 1;

    printf("Custom Barrier : \n");
    for (unsigned i = 0; i < nb_iteration; ++i) {
        reset_matrix(matrix2d);
        reset_buffer(matrix2d);
        stats_array[i] = run_one_custom(matrix2d, number, cpu, user, execution_number);
        //printf("%d iteration -> %.4fs(cpu), %.4fs (user)\n", (i+1), stats_array[i].execution_time_cpu, stats_array[i].execution_time_user);
    }
    exec_stats stats = compute_average(stats_array, nb_iteration);

    return stats;
}


exec_stats run_one_custom(matrix_2d *matrix2d, int thread_number, int measure_cpu, int measure_usr, int execution_number) {

    exec_stats stats;
    init_stats(&stats);
    // if -m, start chrono
    clock_t clockBegin = 0;
    time_t timeBegin = 0;
    if (measure_cpu) {
        clockBegin = clock();
    }
    if (measure_usr) {
        timeBegin = time(NULL);
    }

    // reset buffer
    reset_buffer(matrix2d);

    // total thread number
    unsigned thread_total = (unsigned) 1 << (thread_number);
    // number of thread per "line"
    int thread_by_line = (int) sqrtl((long)thread_total);
    // block size of a thread
    int size = matrix2d->size / thread_by_line;

    if(!size){
        fprintf(stderr, "error: With %d threads, the size is %d, which is impossible ! \n", thread_total, size );
        return stats;
        //exit(0);
    }

    // init barriers
    barrier_impl = init_barrier(thread_total);

    // init thread chunks
    matrix_chunk ** array_chunk = (matrix_chunk**) malloc(sizeof(matrix_chunk)* thread_total);
    if(array_chunk == NULL){
        fprintf(stderr, "error: Cannot allocate chunk array !\n");
        exit(0);
    }

    for(int i = 0; i < thread_total ;  i++){
        array_chunk[i] = malloc(sizeof(matrix_chunk));
        if(array_chunk[i] == NULL){
            fprintf(stderr, "error: Cannot create chunk # %d\n", i);
            exit(0);
        }
        array_chunk[i] = init_chunk(array_chunk[i], size, i, thread_by_line, execution_number, matrix2d);
    }

    // init threads
    pthread_t  array[thread_total];
    for(int i = 0; i < thread_total; i++){
        if(array_chunk[i] == NULL){
            fprintf(stderr, "error: Cannot create chunk # %d\n", i);
            exit(0);
        }

        if (pthread_create(&array[i], NULL, (void*) main_custom_thread, array_chunk[i]) != 0) {
            fprintf(stderr, "error: Cannot create custom thread # %d\n", i);
            break;
        }
    }

    // join threads
    void * retvals[thread_total];
    for (int i = 0; i < thread_total; ++i) {
        if (pthread_join(array[i], &retvals[i]) != 0) {
            fprintf(stderr, "error: Cannot join thread # %d\n", i);
        }
    }

    // if -m, stop the chrono
    if (measure_cpu) {
        stats.execution_time_cpu = (double) (clock() - clockBegin) / CLOCKS_PER_SEC;
    }
    if (measure_usr) {
        stats.execution_time_user = time(NULL) - timeBegin;
    }
    return stats;
}