//
// Created by Nicolas on 20/02/2016.
//

#include "Matrix2D.h"

#ifndef PROG_CONC_DIFF_SIMULATOR_H
#define PROG_CONC_DIFF_SIMULATOR_H

#define NB_ITERATION 10

typedef struct {
    double execution_time_cpu;
    double execution_time_user;
} exec_stats;

exec_stats run_one_iterative(matrix_2d *, int measure_cpu, int measure_usr, int execution_number);

exec_stats run_one_posix(matrix_2d *matrix2d, int thread_number, int measure_cpu, int measure_usr, int execution_number);

exec_stats runIterative(matrix_2d *matrix2d, int measure_cpu, int measure_usr, int execution_number);

exec_stats runThreadPosix(matrix_2d * matrix2d, int number, int cpu, int user, int execution_number);

void init_stats(exec_stats * stats);

void print_stats(exec_stats * stats);

#endif //PROG_CONC_DIFF_SIMULATOR_H
