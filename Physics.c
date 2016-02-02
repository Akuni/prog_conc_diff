//
// Created by user on 02/02/16.
//

#include <stdio.h>
#include "Physics.h"
#include "Matrix.h"
#include "Matrix2D.h"


int calculus(matrix_representation *m, int i, float coeff1, float coeff2);

int calculus_2d(matrix_2d *m, int i, int j, float coeff1, float coeff2, int sens);

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

int diffusion_2d(matrix_2d * m, float coeff1, float coeff2, int sens){
    matrix_2d result;
    init_matrix_2d(m->size, m->middle_index, &result);

    // run through matrix
    int i,j;
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; j++){
            result.matrix[i][j] = calculus_2d(m, i, j, coeff1, coeff2, sens);
        }
    }

    // copy results
    for(i = 0; i < m->size; i++){
        m->matrix[i] = result.matrix[i];
    }

    return 0;
}

int calculus_2d(matrix_2d *m, int i, int j, float coeff1, float coeff2, int sens) {
    int left, right = 0;
    if(sens){
        int ipp = i+1;
        int imm = i-1;
        left = 0 <= imm && imm < m->size ? m->matrix[imm][j] : 0;
        right = 0 <= ipp && ipp < m->size ? m->matrix[ipp][j] : 0;
    }else{
        int jpp = j+1;
        int jmm = j-1;
        left = 0 <= jmm && jmm < m->size ? m->matrix[i][jmm] : 0;
        right = 0 <= jpp && jpp < m->size ? m->matrix[i][jpp] : 0;
    }

    return  m->matrix[i][j] * coeff1 + coeff2 *(left + right);
}