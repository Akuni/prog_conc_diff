/**
 * @authors : Nicolas Sarroche
 */


#include <malloc.h>
#include <stdio.h>
#include "Matrix.h"

/**
 * Init matrix representation.
 */
int init_matrix(int size, float max_temp_value, matrix_representation * m){
    m->size = size;
    m->middle_index = size/2;
    m->matrix = malloc(sizeof(float*)*size);
    m->max_temp_value = max_temp_value;
    m->matrix[m->middle_index] = max_temp_value;
    return 0;
}

/**
 * Show matrix content.
 */
void print_matrix(matrix_representation * m){
    printf("Matrix : \n");
    int i;
    for(i = 0; i < m->size; i++){
        printf("%f ", m->matrix[i]);
    }
    printf("\n-------------\n");
}

