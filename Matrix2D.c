//
// Created by user on 02/02/16.
//

#include <stdio.h>
#include <malloc.h>
#include "Matrix2D.h"

int init_matrix(int size, int max_temp_value, matrix_2d * m){
    m->size = size;
    m->middle_index = size/2;
    int i,j;
    for(i = 0; i< size; i++){
        m->array = malloc(sizeof(int)*size);
    }
    m->max_temp_value = max_temp_value;
    for(i = size/2 - 1; i < size/2 + 1; i ++){
        for(j = size/2-1; j<size/2+1; j++){
            m->matrix[i][j] = max_temp_value;
        }
    }
    return 0;
}

/**
 * Show matrix content.
 */
void print_matrix(matrix_2d * m){
    printf("Matrix : \n");
    int i;
    for(i = 0; i < m->size; i++){
        printf("%d ", m->matrix[i]);
    }
    printf("\n-------------\n");
}

