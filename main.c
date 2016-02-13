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
#include <time.h>

#include "Physics.h"

int main(int argc, char **argv) {
    // index to get args
    int opt = 0;
    // various numbers : thread number, number of execution, the size of the problem
    int thread_number = 0, execution_number = 0, problem_coeff_size = 0;
    // various flags : flag to display only quarter, flag  to display executing time
    int flag_quarter = 0, flag_executing_time = 0;
    // the exercise number
    int exercise_number = 0;

    // time variables
    clock_t begin, end;
    // total time spent
    double time_spent;

    while ((opt = getopt(argc, argv, "t:ami:s:e:")) != -1) {
        switch (opt) {
            case 't':
                // t => number of thread
                thread_number = atoi(optarg);
                break;
            case 'a':
                // a => display quarter of the matrix
                flag_quarter = 1;
                break;
            case 'm':
                // m => display execution time
                flag_executing_time = 1;
                break;
            case 'i':
                // i => number of execution (10000 default)
                execution_number = atoi(optarg);
                break;
            case 's':
                // s => problem size
                problem_coeff_size = atoi(optarg);
                if(problem_coeff_size < 0 ) problem_coeff_size = 0;
                if(problem_coeff_size > 9)  problem_coeff_size = 9;

                break;
            case 'e':
                // e => exercise's number (1 to 5)
                exercise_number = atoi(optarg);
                if(exercise_number < 1) execution_number = 1;
                if(exercise_number > 5) execution_number = 5;
                break;
            default:
                /* '?' */
                fprintf(stderr,
                        "Usage: %s [-t thead], [-a] firstquater,[-m] display executing time, [-i number] number of executions, [-s int] size of the problem, [-e number] execution number  \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // At least exponent of 4
    problem_coeff_size += 4;
    // generate problem size 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192
    int problem_size = 1 << (problem_coeff_size);
    printf("problem size:%d\n", problem_size);

    // if -m, start chrono
    if (flag_executing_time) {
        printf("starting chrono : . . .\n");
        begin = clock();
    }
    // init the 2D matrix
    matrix_2d matrix2d;
    int status = init_matrix_2d(problem_size, 50000, &matrix2d);
    if(status == -1){
        printf("couldn't create the matrix ! \n");
        return -1;
    }

    // start process of diffusion
    switch(exercise_number){
        case 0:
            // no thread
            update_matrix(&matrix2d, execution_number);
            break;
        case 1: // with thread posix
        case 2: // with thread variable
        case 3: // with thread mutex
        case 4: // with OpenCL CPU
        case 5: // with OpenCL GPU
        default:
            break;
    }

    // if -m, stop the chrono and display time
    if (flag_executing_time) {
        end = clock();
        time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        printf("execution time : %lf\n", time_spent);
    }

    // if -a, display the top left quarter of the matrix
    if(flag_quarter){
        print_matrix_2d_quarter(&matrix2d);
    }

    free_matrix(&matrix2d);
}



// old matrix things
/*
matrix_representation m;
int status = init_matrix(problem_size, 256, &m);
print_matrix(&m);
int i;
for (i = 0; i < 10; i++) {
    diffusion(&m, 4 / 6.f, 1 / 6.f);
    print_matrix(&m);
}
 */


