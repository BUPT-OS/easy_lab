#include <iostream>
#include <time.h>
#include <string.h>
#include "main.h"
#include "matrix.h"
#include "multiply.h"

double matrix1[N][M];
double matrix2[M][P];
double result_matrix[N][P];
#ifdef JUDGE_RIGHT
double right_result[N][P];
#endif /*JUDGE_RIGHT*/

int main()
{
    printf("[LOG] N=%d, M=%d, P=%d\n", N, M, P);
    srand((unsigned) time(NULL));
    random_init_matrix((double *) matrix1, N, M);
    random_init_matrix((double *) matrix2, M, P);

    #ifdef JUDGE_RIGHT
    printf("[LOG] JUDGE_RIGHT\n");
    memset(result_matrix, 0, sizeof(double) * N * P);
    memset(right_result,  0, sizeof(double) * N * P);
    // right result
    basic_matrix_multiplication(matrix1, matrix2, right_result);
    // your result
    matrix_multiplication(matrix1, matrix2, result_matrix);
    // judge
    bool result_is_right = judge_right((double *) result_matrix, (double *) right_result, N, P);
    if(result_is_right) {
        printf("[LOG] Accepted\n");
    } else {
        printf("[LOG] Wrong answer\n");
    }
    return 0;
    #endif /*JUDGE_RIGHT*/

    printf("[LOG] JUDGE_TIME\n");
    struct timespec start, end;
    int loop = 5;
    double time_used_sum = 0.;
    for(int i = 0; i < loop; ++i)
    {
        memset(result_matrix, 0, sizeof(double) * N * P);
        clock_gettime(CLOCK_REALTIME, &start);
        matrix_multiplication(matrix1, matrix2, result_matrix);
        clock_gettime(CLOCK_REALTIME, &end);

        double time_used = (double)(end.tv_sec - start.tv_sec) * 1e6 + (double)(end.tv_nsec - start.tv_nsec) / 1e3;
        printf("[LOG] loop=%d, time=%f us\n", i, time_used);
        time_used_sum += time_used;
    }
    double average_time = time_used_sum / (double)loop;
    printf("[LOG] average time=%f us\n", average_time);
    printf("[LOG] GFlops = %f\n", 2.0 * N * M * P * 1.0e-09 / (average_time / 1.0e6));
    return 0;
}