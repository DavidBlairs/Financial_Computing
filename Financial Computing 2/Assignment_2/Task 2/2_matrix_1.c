#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void normalizeVector(double*, int);
double calcNorm2(double*, int, int, int);
double dotProduct(double*, double*, int, int, int);
void vecSub(double*, double*, double*, int, int, int);
void matVecMul(double* A, double* x, double* y, int n, int id, int num);

double F(double);

int main(int argc, char *argv[]) {
    int id, num, n;
    double *A, *x, *y, *z, start_time, end_time;
    double eps = 1e-10, d = 1, s, lambda;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &num);

    /* read n -- problem size */
    n = atoi(argv[1]);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* Initialize Matrix A and vectors x, y, z */
    A = (double*) malloc(n * n * sizeof(double));
    x = (double*) malloc(n * sizeof(double));
    y = (double*) malloc(n * sizeof(double));
    z = (double*) malloc(n * sizeof(double));

    if (id == 0) {
        start_time = MPI_Wtime();
        /* Set A and x. */
        double h = ((double) 2) / n;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                A[(i * n) + j] = pow(h, -1) * ((2 * F((j - i) * h))
                    - F((j - i + 1) * h) - F((j - i - 1) * h));
            }
        }

        for (int i = 0; i < n; i++) {
            x[i] = 1 / sqrt(n);
        }
        end_time = MPI_Wtime();
        printf("Matrix Setup Time: %f\n", end_time - start_time);
    }
    MPI_Bcast(A, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Start Power Iteration */
    start_time = MPI_Wtime();
    while (d >= eps) {
        matVecMul(A, x, y, n, id, num); // y = Ax
        s = calcNorm2(y, n, id, num); // s = ||y||_2
        lambda = dotProduct(x, y, n, id, num); // lambda = x^t y
        for (int j = 0; j < n; ++j) {
            z[j] = x[j]; // z = x
            x[j] = y[j] / s; // x = y / s
        }
	vecSub(x, z, y, n, id, num); // y = x - z
        d = calcNorm2(y, n, id, num); // d = ||x - z||_2
    }
    /* End Power Iteration */

    MPI_Finalize();
    end_time = MPI_Wtime();
    if (id == 0){
        printf("Power Iteration Time: %f\n", end_time - start_time);
        printf("Largest Eigenvalue: %f\n", lambda);
    }
    return 0;
}

double F(double z){
    if (z != 0){
        return pow(z, 2) * (log(fabs(z)) - 1.5);
    } else {
        return 0;
    }
}

void matVecMul(double* A, double* x, double* y, int n, int id, int num) {
    int sz = n / num;
    int i0 = id * sz;
    int i1 = (id + 1) * sz;
    if (id == (num - 1)) i1 = n;

    for (int i = i0; i < i1; ++i) {
        y[i] = 0;
        for (int j = 0; j < n; ++j) {
            y[i] += A[i * n + j] * x[j];
        }
    }

    MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, y, sz, MPI_DOUBLE, MPI_COMM_WORLD);
}

double calcNorm2(double* v, int n, int id, int num) {
    double norm = 0;
    for (int i = 0; i < n; ++i) {
        norm += v[i] * v[i];
    }
    norm = sqrt(norm);
    return norm;
}

double dotProduct(double* v1, double* v2, int n, int id, int num) {
    double result = 0;
    for (int i = 0; i < n; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

void vecSub(double* v1, double* v2, double* v3, int n, int id, int num) {
    for (int i = 0; i < n; ++i) {
        v3[i] = v1[i] - v2[i];
    }
}