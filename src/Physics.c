/**
 * @authors : Nicolas Sarroche
 */


#include "Physics.h"
#include "Matrix2D.h"
#include "Matrix.h"


float calculus(matrix_representation *m, int i, float coeff1, float coeff2);

float calculus_2d(matrix_2d *m, int i, int j, float coeff1, float coeff2, int sens);


float calculus(matrix_representation *m, int i, float coeff1, float coeff2){
    int ipp = i+1;
    int imm = i-1;
    float left = 0 <= imm && imm < m->size ? m->matrix[imm] : 0;
    float right = 0 <= ipp && ipp < m->size ? m->matrix[ipp] : 0;
    return  m->matrix[i] * coeff1 + coeff2 *(left + right);
}

int diffusion_2d(matrix_2d * m, float coeff1, float coeff2, int sens){
    // run through matrix
    int i,j;
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; j++){
            m->buffer[i][j] = calculus_2d(m, i, j, coeff1, coeff2, sens);
        }
    }

    /* Copy from buffer */
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; ++j) {
            m->matrix[i][j] = m->buffer[i][j];
        }
    }
    return 0;
}

int diffusion_2d_section(section* s, float coeff1, float coeff2, int sens) {
    matrix_2d* m = s->matrix;
    for (int i = s->startX; i < s->endX; ++i) {
        for (int j = s->startY; j < s->endY; ++j) {
            m->buffer[i][j] = calculus_2d(m, i, j, coeff1, coeff2, sens);
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