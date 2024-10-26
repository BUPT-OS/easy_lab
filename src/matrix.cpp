#include "matrix.h"

void random_init_matrix(double *matrix, int n, int m)
{
    int length = n * m;
    for(int index = 0; index < length; ++index, ++matrix) {
        *matrix = rand() % 10;
    }
}

void basic_matrix_multiplication(double matrix1[N][M], double matrix2[M][P], double result_matrix[N][P])
{
    for(int row = 0; row < N; ++row)
        for(int col = 0; col < P; ++col)
            for(int mid = 0; mid < M; ++mid)
                result_matrix[row][col] += matrix1[row][mid] * matrix2[mid][col];
}

bool judge_right(double *pointer1, double *pointer2, int n, int m)
{
    int length = n * m;
    const double gap = 1e-5;
    double num1, num2;
    for(int index = 0; index < length; ++index, ++pointer1, ++pointer2) {
        num1 = *pointer1;
        num2 = *pointer2;
        if(std::abs(num1 - num2) > gap) {
            return false;
        }
    }
    return true;
}