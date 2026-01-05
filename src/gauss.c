#include "gauss.h"
#include <math.h>

/**
 * Zwraca 0 - eliminacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int n = mat->r;

    for(int k = 0; k < n - 1; k++) {
        
        int kmax = k;
        for (int i = k + 1; i < n; i++) 
            if (fabs(mat->data[i][k]) > fabs(mat->data[kmax][k])) 
                kmax = i;
        
        if (kmax != k) {
            double *tmp = mat->data[k];
            mat->data[k] = mat->data[kmax];
            mat->data[kmax] = tmp;

            double *tmp_b = b->data[k];
            b->data[k] = b->data[kmax];
            b->data[kmax] = tmp_b;
        }

        for(int i = k + 1; i < n; i++) {
            if (fabs(mat->data[k][k]) < 1e-12) return 1;

            double factor = mat->data[i][k] / mat->data[k][k];

            for(int j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }
            b->data[i][0] -= factor * b->data[k][0];
        }
    }
    
    if (fabs(mat->data[n-1][n-1]) < 1e-12) return 1;

    return 0;
}