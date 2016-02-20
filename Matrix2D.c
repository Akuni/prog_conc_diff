//
// Created by user on 02/02/16.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "Matrix2D.h"
#include "Physics.h"

int init_matrix_2d(int size, float max_temp_value, matrix_2d * m){
    m->size = size;
    // middle is at size / 2
    m->middle_index = size>>1;
    // range/2 is size / 8
    m->half_range = size>>4;
    int i;
    // init matrix
    if (( m->matrix = malloc( size*sizeof( float * ))) == NULL ) { /*error*/return -1;}
    // init rows
    for ( i = 0; i < size; i++ ) {
        if (( m->matrix[i] = malloc(sizeof(float)*  size )) == NULL )
        { /* error */  return -1;}
        memset(m->matrix[i], 0, sizeof(float) * size);
    }
    // set max temp
    m->max_temp_value = max_temp_value;
    // set some cells to max temp
    set_middle_to_max_temp(m);
    return 0;
}

void reset_matrix(matrix_2d *m) {
    for (unsigned i = 0; i < m->size; ++i) {
        memset(m->matrix[i], 0, sizeof(float) * m->size);
    }
    set_middle_to_max_temp(m);
}

/**
 * Show matrix content.
 */
void print_matrix_2d(matrix_2d * m){
    printf("Matrix : \n");
    int i,j;
    for(j = 0; j < m->size; j++){
        for(i = 0; i < m->size; i++){
            printf("%d\t\t\t", (int) m->matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n-------------\n");
}

/**
 * Update the 2D matrix by applying 2d diffusion on both X and Y axis.
 */
int update_matrix(matrix_2d * m, int exec_number){
    int i;
    for(i = 0; i < exec_number; i++){
        diffusion_2d(m, 4 / 6.f, 1 / 6.f, 0);
        diffusion_2d(m, 4 / 6.f, 1 / 6.f, 1);
        set_middle_to_max_temp(m);
    }
    return 0;
}

/**
 * Only display the top left quarter of the matrix.
 */
void print_matrix_2d_quarter(matrix_2d * m){
    printf("Matrix : \n");
    int i,j;
    for(j = 0; j < m->middle_index; j++){
        for(i = 0; i < m->middle_index; i++){
            printf("%d\t\t", (int) m->matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n-------------\n");
}

/**
 * Set or reset middle squares to the max temp value.
 */
void set_middle_to_max_temp(matrix_2d * m){
    int i,j;
    for(i = m->middle_index - m->half_range; i <= m->middle_index + m->half_range; i ++){
        for(j = m->middle_index - m->half_range; j<=m->middle_index + m->half_range; j++){
            m->matrix[i][j] = m->max_temp_value;
        }
    }
}

/**
 * Free the matrix
 */
void free_matrix(matrix_2d * m) {
    for (unsigned i = 0; i < m->size; ++i) {
        free(m->matrix[i]);
    }
    free (m);
}