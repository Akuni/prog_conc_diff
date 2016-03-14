/**
 * @authors : Nicolas Lecourtois
 */


#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "Matrix2D.h"
#include "simulator.h"

exec_stats compute_average(exec_stats stats_array[10], int array_length);

/**
 * Run the simulation once
 * If execution stats are ordered, return them.
 */
exec_stats run_iterative_once(matrix_2d *matrix2d, int measure_cpu, int measure_usr, int execution_number) {
    exec_stats stats; init_stats(&stats);
    // if -m, start chrono
    clock_t clockBegin = 0;time_t timeBegin = 0;
    if (measure_cpu) clockBegin = clock();
    if (measure_usr) timeBegin = time(NULL);

    // init the 2D matrix
    reset_matrix(matrix2d);
    update_matrix(matrix2d, execution_number);

    // if -m, stop the chrono
    if (measure_cpu) stats.execution_time_cpu = (double) (clock() - clockBegin) / CLOCKS_PER_SEC;
    if (measure_usr) stats.execution_time_user = time(NULL) - timeBegin;
    return stats;
}

/**
 * Run the simulation once or several times depending on whether we need stats or not.
 */
exec_stats run_iterative(matrix_2d *matrix2d, int measure_cpu, int measure_usr, int execution_number) {
    exec_stats stats_array[NB_ITERATION];
    int flag_must_make_average = measure_cpu || measure_usr;
    int nb_iteration = flag_must_make_average ? NB_ITERATION : 1;

    for (unsigned i = 0; i < nb_iteration; ++i) {
        stats_array[i] = run_iterative_once(matrix2d, measure_cpu, measure_usr, execution_number);
    }

    exec_stats stats = compute_average(stats_array, nb_iteration);

    return stats;
}

exec_stats run_thread(matrix_2d *matrix2d, sim_parameters *p, int thread_number) {
    exec_stats stats_array[NB_ITERATION];
    int flag_must_make_average = p->flag_execution_time_cpu || p->flag_execution_time_user;
    int nb_iteration = flag_must_make_average ? NB_ITERATION : 1;

    for (unsigned iter = 0; iter < nb_iteration; ++iter) {
        stats_array[iter] = run_thread_once(matrix2d, p, thread_number);
    }

    exec_stats stats = compute_average(stats_array, nb_iteration);
    return stats;
}

/**
 * Run the diffusion for each division
 */
exec_stats run_thread_once(matrix_2d *matrix2d, sim_parameters* p, int thread_number) {
    exec_stats stats; init_stats(&stats);
    // if -m, start chrono
    clock_t clockBegin = 0;time_t timeBegin = 0;
    if (p->flag_execution_time_cpu) clockBegin = clock();
    if (p->flag_execution_time_user) timeBegin = time(NULL);

    // init the 2D matrix
    reset_matrix(matrix2d);

    // Compute info thread
    int nb_sec_side = 1 << thread_number;
    int nb_thread = 1 << (thread_number*2);
    int size_section = matrix2d->size / nb_sec_side;

    pthread_barrier_t section_barrier, thread_barrier;

    pthread_barrier_init(&section_barrier, NULL, nb_thread);
    pthread_barrier_init(&thread_barrier, NULL, nb_thread+1);
    for(unsigned i = 0; i < nb_sec_side; ++i) {
        for(unsigned j = 0; j < nb_sec_side; ++j) {
            pthread_t t;
            section* s;

            if ((s = malloc(sizeof(section))) == NULL) {
                perror("Couldn't malloc for a new Section\n");
                exit(EXIT_FAILURE);
            }

            s->matrix = matrix2d;
            s->startX = j * size_section;
            s->startY = i * size_section;
            s->endX = s->startX + size_section;
            s->endY = s->startY + size_section;
            s->section_barrier = &section_barrier;
            s->thread_barrier = &thread_barrier;
            s->nb_exec = p->execution_number;

            pthread_create(&t, NULL, &diffusion_thread, s);
        }
    }
    pthread_barrier_wait(&thread_barrier);

    pthread_barrier_destroy(&section_barrier);
    pthread_barrier_destroy(&thread_barrier);

    // if -m, stop the chrono
    if (p->flag_execution_time_cpu) stats.execution_time_cpu = (double) (clock() - clockBegin) / CLOCKS_PER_SEC;
    if (p->flag_execution_time_user) stats.execution_time_user = time(NULL) - timeBegin;

    return stats;
}

/**
 * Compute the average execution stats
 */
exec_stats compute_average(exec_stats stats_array[], int array_length) {
    exec_stats stats;
    // If we don't have enough stats to ignore the first and the last, we chose the first value
    if (1 <= array_length && array_length < 3) {
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

int set_sim_parameters(int argc, char **argv, sim_parameters* p) {
    // index to get args
    int opt = 0;
    while ((opt = getopt(argc, argv, "t:amMi:s:e:")) != -1) {
        char c;
        switch (opt) {
            case 't':
                // t => number of thread
                p->thread_number = atoi(optarg);
                break;
            case 'a':
                // a => display quarter of the matrix
                p->flag_quarter = 1;
                break;
            case 'm':
                // m => display execution time (CPU)
                p->flag_execution_time_cpu = 1;
                break;
            case 'M':
                // M => display execution time (USER)
                p->flag_execution_time_user = 1;
                break;
            case 'i':
                // i => number of execution (10000 default)
                p->execution_number = atoi(optarg);
                break;
            case 's':
                // s => problem size
                p->nb_sizes = strlen(optarg);
                if ((p->array_problem_coeff_size = malloc(p->nb_sizes * sizeof(int))) == NULL) return 0; /*error*/
                for (int i = 0; i < p->nb_sizes; ++i) {
                    c = optarg[i];
                    p->array_problem_coeff_size[i] = atoi(&c);
                    if(p->array_problem_coeff_size[i] < 0)  p->array_problem_coeff_size[i] = 0;
                    if(p->array_problem_coeff_size[i] > 9)  p->array_problem_coeff_size[i] = 9;
                }


                break;
            case 'e':
                // e => exercise's number (1 to 5)
                p->exercise_number = atoi(optarg);
                if(p->exercise_number < 0) p->exercise_number = 0;
                if(p->exercise_number > 5) p->exercise_number = 5;
                break;
            default:
                /* '?' */
                fprintf(stderr,
                        "Usage: %s [-t thead], [-a] firstquater,[-m] display executing time, [-i number] number of executions, [-s int] size of the problem, [-e number] execution number  \n",
                        argv[0]);
                return 0;
        }
    }
    return 1;
}

void free_sim_parameters(sim_parameters *p) {
    free(p->array_problem_coeff_size);
}
