#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double F(double z){
        if (z != 0){
                return pow(z, 2) * (log(fabs(z)) - 1.5);
        } else {
                return 0;
        }
}

double A_N(int N){
        int iterations;
        double *A, *x, *y, *z, s = 0, lambda = 0, total = 0, st = 0, et = 0, t = 0, d = 1, h = pow(N, -1), e = 1e-10;
        if ((x = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((x = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((y = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((z = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((A = (double*)malloc(N * N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};   

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                        A[(i * N) + j] = pow(h, -1) * ((2 * F((j - i) * h))
                                - F((j - i + 1) * h) - F((j - i - 1) * h));
                }
        }

        #pragma omp parallel for
        for (int i = 0; i < N; i++)
                x[i] = pow(sqrt(N), -1);

        st = omp_get_wtime();
        while (d >= e){
                #pragma omp parallel for
                for (int i = 0; i < N; i++){
                        y[i] = 0;
                        #pragma omp parallel for reduction(+:y[i])
                        for (int j = 0; j < N; j++){
                                y[i] += A[(i * N) + j] * x[j];
                        }
                }

                s = 0;
                #pragma omp parallel for reduction(+:s)
                for (int i = 0; i < N; i++)
                        s += pow(y[i], 2);
                s = sqrt(s);

                lambda = 0;
                #pragma omp parallel for reduction(+:lambda)
                for (int i = 0; i < N; i++)
                        lambda += x[i] * y[i];

                #pragma omp parallel for
                for (int i = 0; i < N; i++)
                        z[i] = x[i];

                #pragma omp parallel for
                for (int i = 0; i < N; i++)
                        x[i] = y[i] / s;

                d = 0;
                #pragma omp parallel for reduction(+:d)
                for (int i = 0; i < N; i++)
                        d += pow(x[i] - z[i], 2);

                d = sqrt(d);
                iterations += 1;
        }
        et = omp_get_wtime();

        free(x);
        free(y);
        free(z);
        free(A);

        return(et - st);
}

int populate_times(int N, double* times, double* speeds){
        double first_time = 0;
        int thread_index = 0;

        for (int threads = 1; threads <= 16; threads *= 2){
                double current_time = 0;

                omp_set_num_threads(threads);
                current_time = A_N(N);

                if (threads == 1){
                        first_time = current_time;
                }

                times[thread_index] = current_time;
                speeds[thread_index] = current_time - first_time;

                thread_index += 1;
        }
        return(0);
}

int main(){
        double times[5], speeds[5];
        char line_split[] = "|----------|----------|----------|----------|----------|----------|----------|\n";
        char line_end[]   = "------------------------------------------------------------------------------\n";

        printf(line_end);
        printf("|   Type   |    N     |    t1    |   t2     |    t4    |    t8    |    t16   |\n");
        printf(line_split);

        for (int N = 256; N <= 4096; N *= 2){
                for (int type_index = 0; type_index < 2; type_index++){
                        populate_times(N, times, speeds);

                        if (type_index == 0){
                                printf("|   Time   |");
                        } else {
                                printf("| Speed-Up |");
                        }

                        printf(" %8d |", N);

                        for (int thread_index = 0; thread_index < 5; thread_index++){
                                if (type_index == 0){
                                        printf(" %7.3fs |", times[thread_index]);
                                } else {
                                        printf(" %7.3fs |", speeds[thread_index]);
                                }
                        }
                        printf("\n");
                }
                if (N != 4096){
                        printf(line_split);
                } else {
                        printf(line_end);
                }
        }

        return 0;
}