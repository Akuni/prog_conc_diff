/*
 * main.c
 * 
 * Copyright 2016 Akuni <user@Axxx>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#include "Physics.h"
#include "simulator.h"
struct rusage;

int main(int argc, char **argv) {
    // index to get args
    int opt = 0;
    // different problem size to be executed
    int *array_problem_coeff_size;
    int nb_sizes = 0;
    // various numbers : thread number, number of execution, the size of the problem
    int thread_number = 0, execution_number = 10000, problem_coeff_size = 0;
    // various flags : flag to display only quarter, flag  to display executing time
    int flag_quarter = 0, flag_execution_time_cpu = 0, flag_execution_time_user = 0;
    // the exercise number
    int exercise_number = 0;

    // execution statistics
    exec_stats stats;
    char c;

    while ((opt = getopt(argc, argv, "t:amMi:s:e:")) != -1) {
        switch (opt) {
            case 't':
                // t => number of thread
                thread_number = atoi(optarg);
                if(thread_number < 0) thread_number = 0;
                if(thread_number > 5) thread_number = 5;
                thread_number *= 2;
                break;
            case 'a':
                // a => display quarter of the matrix
                flag_quarter = 1;
                break;
            case 'm':
                // m => display execution time (CPU)
                flag_execution_time_cpu = 1;
                break;
            case 'M':
                // M => display execution time (USER)
                flag_execution_time_user = 1;
                break;
            case 'i':
                // i => number of execution (10000 default)
                execution_number = atoi(optarg);
                break;
            case 's':
                // s => problem size
                nb_sizes = strlen(optarg);
                array_problem_coeff_size = malloc(nb_sizes * sizeof(int));
                for (int i = 0; i < nb_sizes; ++i) {
                    c = optarg[i];
                    array_problem_coeff_size[i] = atoi(&c);
                    if(array_problem_coeff_size[i] < 0 ) array_problem_coeff_size[i] = 0;
                    if(array_problem_coeff_size[i] > 9)  array_problem_coeff_size[i] = 9;
                }


                break;
            case 'e':
                // e => exercise's number (1 to 5)
                exercise_number = atoi(optarg);
                if(exercise_number < 0) exercise_number = 0;
                if(exercise_number > 5) exercise_number = 5;
                break;
            default:
                /* '?' */
                fprintf(stderr,
                        "Usage: %s [-t thead], [-a] firstquater,[-m] display executing time, [-i number] number of executions, [-s int] size of the problem, [-e number] execution number  \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    struct rusage usage;

    for (int i = 0; i < nb_sizes; ++i) {
        getrusage(RUSAGE_SELF, &usage);
        problem_coeff_size = array_problem_coeff_size[i];
        // At least exponent of 4
        problem_coeff_size += 4;
        // generate problem size 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192
        int problem_size = 1 << (problem_coeff_size);
        printf("problem size:%d\n", problem_size);

        // init the 2D matrix
        matrix_2d matrix2d;
        int status = init_matrix_2d(problem_size, 128, &matrix2d);
        if(status == -1){
            printf("couldn't create the matrix ! \n");
            return -1;
        }

        // start process of diffusion
        switch(exercise_number){
            case 0:
                // no thread
                stats = runIterative(&matrix2d, flag_execution_time_cpu, flag_execution_time_user, execution_number);
                break;
            case 1: // with thread posix
                stats = runThreadPosix(&matrix2d, thread_number,flag_execution_time_cpu, flag_execution_time_user, execution_number);
                break;
            case 2: // with thread variable
            case 3: // with thread mutex
            case 4: // with OpenCL CPU
            case 5: // with OpenCL GPU
            default:
                break;
        }

        // if -m, display time
        if (flag_execution_time_cpu) {
            printf("Execution time (cpu) : %lf\n", stats.execution_time_cpu);
        }
        if (flag_execution_time_user) {
            printf("Execution time (user) : %lf\n", stats.execution_time_user);
        }

        // if -a, display the top left quarter of the matrix
        if(flag_quarter){
            print_matrix_2d_quarter(&matrix2d);
        }
        getrusage(RUSAGE_SELF, &usage);
        printf("Memory usage : %ld\n", usage.ru_maxrss);
        free_matrix(&matrix2d);
    }

    free(array_problem_coeff_size);
}

