//
// Created by LECOURTOIS Nicolas & SARROCHE Nicolas on 02/02/16.
//

#include "Physics.h"


float calculus_2d(matrix_2d *m, int i, int j, float coeff1, float coeff2, int sens);

int diffusion_2d(matrix_2d * m, float coeff1, float coeff2, int sens){

    reset_buffer(m);

    // run through matrix
    int i,j;
    for(i = 0; i < m->size; i++){
        if(!m->matrix[m->middle_index][i]) continue;
        for(j = 0; j < m->size; j++){
            m->buffer[i][j] = calculus_2d(m, i, j, coeff1, coeff2, sens);
        }
    }

    // copy results
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; ++j) {
            m->matrix[i][j] = m->buffer[i][j];
        }
    }
    return 0;
}

float calculus_2d(matrix_2d *m, int i, int j, float coeff1, float coeff2, int sens) {
    float right,left;
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

int diffusion_2d_chunk(matrix_chunk * m, float coeff1, float coeff2, int sens){

    // run through matrix
    int i,j;
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; j++){
            // Todo check optimization condition
            /*if(!m->matrix2d->matrix[m->size*m->idX + i ][m->matrix2d->middle_index])
                continue;*/
            m->matrix2d->buffer[m->size*m->idX+i][m->size*m->idY+j] = calculus_2d(m->matrix2d, m->size*m->idX+i, m->size*m->idY+j, coeff1, coeff2, sens);
        }
    }

    return 0;
}

