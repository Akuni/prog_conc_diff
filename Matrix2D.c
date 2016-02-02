//
// Created by user on 02/02/16.
//

#include <stdio.h>
#include <malloc.h>
#include "Matrix2D.h"
#include "Physics.h"

int init_matrix_2d(int size, int max_temp_value, matrix_2d * m){
    m->size = size;
    m->middle_index = size/2;
    int i,j;
    // init matrix
    if (( m->matrix = malloc( size*sizeof( int * ))) == NULL ) { /* error */ }
    // init rows
    for ( i = 0; i < size; i++ ) {
        if (( m->matrix[i] = malloc(sizeof(int)*  size )) == NULL )
        { /* error */ }
    }
    // set max temp
    m->max_temp_value = max_temp_value;
    // set some cells to max temp
    for(i = size/2 - 1; i <= size/2 + 1; i ++){
        for(j = size/2-1; j<=size/2+1; j++){
            m->matrix[i][j] = max_temp_value;
        }
    }
    return 0;
}

/**
 * Show matrix content.
 */
void print_matrix_2d(matrix_2d * m){
    printf("Matrix : \n");
    int i,j;
    for(j = 0; j < m->size; j++){
        for(i = 0; i < m->size; i++){
            printf("%d\t\t\t", m->matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n-------------\n");
}

int update_matrix(matrix_2d * m){
    int i;
    for(i = 0; i < 10; i++){
        diffusion_2d(m, 4 / 6.f, 1 / 6.f, 0);
        diffusion_2d(m, 4 / 6.f, 1 / 6.f, 1);
        print_matrix_2d(m);
    }
}

