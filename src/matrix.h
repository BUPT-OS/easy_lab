#ifndef _MATRIX_
#define _MATRIX_

#include <stdlib.h>
#include "main.h"

void random_init_matrix(double *matrix, int n, int m);

void basic_matrix_multiplication(double matrix1[N][M], double matrix2[M][P], double result_matrix[N][P]);

bool judge_right(double *pointer1, double *pointer2, int n, int m);

#endif /*_MATRIX_*/
