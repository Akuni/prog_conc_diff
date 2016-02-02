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

#include "Matrix.h"
#include "Physics.h"
#include "Matrix2D.h"

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
                thread_number = atoi(optarg);
                break;
            case 'a':
                flag_quarter = 1;
                break;
            case 'm':
                flag_executing_time = 1;
                break;
            case 'i':
                execution_number = atoi(optarg);
                break;
            case 's':
                // todo verification of the number 0 < i < 9
                problem_coeff_size = atoi(optarg);
                break;
            case 'e':
                exercise_number = atoi(optarg);
                break;
            default:
                /* '?' */
                fprintf(stderr,
                        "Usage: %s [-t thead], [-a] firstquater,[-m] display executing time, [-i number] number of executions, [-s int] size of the problem, [-e number] execution number  \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    problem_coeff_size += 4;
    printf("pb:%d\n", problem_coeff_size);
    int problem_size = 1 << (problem_coeff_size);


    if (flag_executing_time) {

        begin = clock();
    }
    matrix_2d matrix2d;
    int status2 = init_matrix_2d(problem_size, 50000, &matrix2d);
    print_matrix_2d(&matrix2d);

    update_matrix(&matrix2d);

    if (flag_executing_time) {
        end = clock();
        time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        printf("execution time : %lf\n", time_spent);
    }
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


