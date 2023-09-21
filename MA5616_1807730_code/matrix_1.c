#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// function to populate the matrix
double F(double z){
        if (z != 0){
                return pow(z, 2) * (log(fabs(z)) - 1.5);
        } else {
                return 0;
        }
}

// function to perform power iteration algorithm  
double A_N(int N){
        // declare variables
        int iterations;
        double *A, *x, *y, *z, s, lambda, total, st, et, t, d = 1, h = pow(N, -1), e = 0.0001;

        // set start time
        st = omp_get_wtime();

        // allocate dynamic memory
        if ((x = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((x = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((y = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((z = (double*)malloc(N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};
        if ((A = (double*)malloc(N * N * sizeof(double))) == NULL){printf("Memory Allocation Error."); return 1;};

        // populate the matrix 
        for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                        A[(i * N) + j] = pow(h, -1) * ((2 * F((j - i) * h))
                                - F((j - i + 1) * h) - F((j - i - 1) * h));
                }
        }

        // set x 
        for (int i = 0; i < N; i++)
                x[i] = pow(sqrt(N), -1);

        // while d is larger than the error threshold
        while (d >= e){
                // y = Ax
                for (int i = 0; i < N; i++){
                        y[i] = 0;
                        for (int j = 0; j < N; j++){
                                y[i] += A[(i * N) + j] * x[j];
                        }
                }

                // ||y||_2 (2-norm)
                s = 0;
                for (int i = 0; i < N; i++)
                        s += pow(y[i], 2);
                s = sqrt(s);

                // lambda = x^t y
                lambda = 0;
                for (int i = 0; i < N; i++)
                        lambda += x[i] * y[i];

                // z = x
                for (int i = 0; i < N; i++)
                        z[i] = x[i];

                // x = y / s
                for (int i = 0; i < N; i++)
                        x[i] = y[i] / s;

                // d = ||x - z||_2 (2-norm)
                d = 0;
                for (int i = 0; i < N; i++)
                        d += pow(x[i] - z[i], 2);
                d = sqrt(d);
                iterations += 1;
        }
        // set end time
        et = omp_get_wtime();

        // print results
        printf("N = %d; Iterations = %d; Lambda = %f; Duration = %f\n", N, iterations, lambda, et - st);

        // free up used memory
        free(x);
        free(y);
        free(z);
        free(A);

}

int main(){
        // decalare variables
        int N, v_N;

        // Get the value of N
        printf("Number of Iterations: "); v_N = scanf("%d", &N);
        if (v_N != 1 | N <= 0){printf("Invalid Input.\n"); return 0;}

        // perform the power iteration algorithm
        A_N(N);

        return 0;
}