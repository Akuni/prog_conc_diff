//
// Created by user on 02/02/16.
//

#include <stdio.h>
#include "Physics.h"
#include "Matrix.h"


int calculus(matrix_representation *m, int i, float coeff1, float coeff2);

int diffusion(matrix_representation * m, float coeff1, float coeff2){
    matrix_representation result;
    init_matrix(m->size, m->middle_index, &result);

    // run through matrix
    int i;
    for(i = 0; i < m->size; i++){
        result.matrix[i] = calculus(m, i, coeff1, coeff2);
    }

    // copy results
    for(i = 0; i < m->size; i++){
        m->matrix[i] = result.matrix[i];
    }

    return 0;
}



int calculus(matrix_representation *m, int i, float coeff1, float coeff2){
    int ipp = i+1;
    int imm = i-1;
    int left = 0 <= imm && imm < m->size ? m->matrix[imm] : 0;
    int right = 0 <= ipp && ipp < m->size ? m->matrix[ipp] : 0;
    return  m->matrix[i] * coeff1 + coeff2 *(left + right);
}