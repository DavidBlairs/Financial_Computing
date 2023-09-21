#include <stdio.h>
#include <math.h>
#include <omp.h>

// function for integrand
double u(double x){
        return exp(x) * sin(x);
}

int main(){
        // setup variables
        double x, y, err, c_val, h, s_time, e_time, time, total = 0;
        int N, v_N, v_x, v_y;

        // get the lower limit for the integral
        printf("Lower Limit: "); v_x = scanf("%lf", &x);
        if (v_x != 1){printf("Invalid Input.\n"); return 0;};

        // get the upper limit for the integral
        printf("Upper Limit: "); v_y = scanf("%lf", &y);
        if (v_y != 1){printf("Invalid Input.\n"); return 0;};

        // get the number of iterations
        printf("Number of Iterations: "); v_N = scanf("%d", &N);
        if (v_N != 1 | N <= 0){printf("Invalid Input.\n"); return 0;};

        // calculate width of segments
        h = (y - x) / N;

        // set the start time
        s_time = omp_get_wtime();

        // for each segment
        for (int i = 1; i < N + 1; i++){
                // calculate its area and add to total
                total += h * u(x + ((i - 0.5) * h));
        }

        // get the end time
        e_time = omp_get_wtime();

        // calculate duration
        time = e_time - s_time;

        // print the results
        printf("N = %d; f(%f, %f) = %f; Duration = %fs;\n", N, x, y, total, time);
}