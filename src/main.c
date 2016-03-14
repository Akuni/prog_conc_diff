/**
 * @authors : Nicolas Sarroche, Nicolas Lecourtois
 */


#include <stdio.h>
#include <stdlib.h>
#include "Physics.h"
#include "simulator.h"

struct rusage;

int main(int argc, char **argv) {
    sim_parameters p;
    if (!(set_sim_parameters(argc, argv, &p))) {
        exit(EXIT_FAILURE);
    }
    // execution statistics
    exec_stats stats;

    for (int i = 0; i < p.nb_sizes; ++i) {
        p.problem_coeff_size = p.array_problem_coeff_size[i];
        // At least exponent of 4
        p.problem_coeff_size += 4;
        // generate problem size 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192
        int problem_size = 1 << (p.problem_coeff_size);
        printf("problem size:%d\n", problem_size);
        printf("nb thread :%d\n", 1 << p.thread_number*2);

        // init the 2D matrix
        matrix_2d matrix2d;
        int status = init_matrix_2d(problem_size, 50000, &matrix2d);
        if(status == -1){
            printf("couldn't create the matrix ! \n");
            return -1;
        }

        // start process of diffusion
        switch(p.exercise_number){
            case 0: // no thread
                stats = run_iterative(&matrix2d, p.flag_execution_time_cpu, p.flag_execution_time_user, p.execution_number);
                //run_thread(&matrix2d, &p, 1);
                break;
            case 1: // with thread posix
                run_thread(&matrix2d, &p, p.thread_number);
                break;
            case 2: // with thread variable
            case 3: // with thread mutex
            case 4: // with OpenCL CPU
            case 5: // with OpenCL GPU
            default:
                break;
        }

        // if -m, display time
        if (p.flag_execution_time_cpu) {
            printf("Execution time (cpu) : %lf\n", stats.execution_time_cpu);
        }
        if (p.flag_execution_time_user) {
            printf("Execution time (user) : %lf\n", stats.execution_time_user);
        }

        // if -a, display the top left quarter of the matrix
        if(p.flag_quarter){
            print_matrix_2d_quarter(&matrix2d);
        }

        free_matrix(&matrix2d);
    }

    free_sim_parameters(&p);
}

