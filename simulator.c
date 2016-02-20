//
// Created by Nicolas on 20/02/2016.
//

#include <time.h>
#include <stdio.h>
#include "Matrix2D.h"
#include "simulator.h"

exec_stats compute_average(exec_stats stats_array[10], int array_length);

/**
 * Run the simulation once
 * If execution stats are ordered, return them.
 */
exec_stats run(matrix_2d *matrix2d, int measure_cpu, int measure_usr, int execution_number) {
    exec_stats stats;
    init_stats(&stats);
    // if -m, start chrono
    clock_t begin = 0, end = 0;
    if (measure_cpu) {
        begin = clock();
    }

    // init the 2D matrix
    reset_matrix(matrix2d);
    update_matrix(matrix2d, execution_number);

    // if -m, stop the chrono
    if (measure_cpu) {
        end = clock();
        stats.execution_time_cpu = (double) (end - begin) / CLOCKS_PER_SEC;
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

    for (unsigned i = 0; i < nb_iteration; ++i) {
        stats_array[i] = run(matrix2d, measure_cpu, measure_usr, execution_number);
    }

    exec_stats stats = compute_average(stats_array, nb_iteration);

    return stats;
}

exec_stats compute_average(exec_stats stats_array[], int array_length) {
    exec_stats stats;
    // If we have not enough stats to ignore the first and the last, we chose the first stats
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

void init_stats(exec_stats * stats) {
    stats->execution_time_cpu = 0;
    stats->execution_time_user = 0;
}

void print_stats(exec_stats * stats) {
    printf("Execution statistics\n");
    printf(" Cpu exec time : %lf\n", stats->execution_time_cpu);
    printf(" User exec time : %lf\n", stats->execution_time_cpu);
}