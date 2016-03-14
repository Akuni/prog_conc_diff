/**
 * @authors : Nicolas Lecourtois
 */


#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix2D.h"

#ifndef PROG_CONC_DIFF_SIMULATOR_H
#define PROG_CONC_DIFF_SIMULATOR_H

#define NB_ITERATION 5

typedef struct {
    double execution_time_cpu;
    double execution_time_user;
} exec_stats;

typedef struct {
    // different problem size to be executed
    int *array_problem_coeff_size, *array_thread_nb, *array_exec;
    int nb_sizes, nb_thread_nb, nb_exec;
    // various numbers : thread number, number of execution, the size of the problem
    int /*thread_number,*/ execution_number, problem_coeff_size;
    // various flags : flag to display only quarter, flag  to display executing time
    int flag_quarter, flag_execution_time_cpu, flag_execution_time_user;
    // the exercise number
    int exercise_number;
} sim_parameters;

exec_stats run_thread(matrix_2d *matrix2d, sim_parameters *p, int thread_number);

exec_stats run_thread_once(matrix_2d *matrix2d, sim_parameters *p, int thread_number);

void init_stats(exec_stats * stats);

void print_stats(exec_stats * stats);

int set_sim_parameters(int argc, char **argv, sim_parameters* p);

void free_sim_parameters(sim_parameters *ptr);


#endif //PROG_CONC_DIFF_SIMULATOR_H
