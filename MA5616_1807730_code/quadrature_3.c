#include <stdio.h>
#include <math.h>
#include <omp.h>

// function for integrand
double u(double x){
        return exp(x) * sin(x);
}

int main(){
        // setup variables
        double err, c_val, h, s_time, e_time, time, error, total, x = 1, y = 2, f_ex = 4.487560;

        // for each value of N
        for (int N = 8; N < 1025; N *= 2){
                // reset total
                total = 0;

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

                // calculate the error
                error = fabs(total - f_ex);

                // print the results
                printf("N = %d; f(%f, %f) = %f; error = %f; Duration = %fs;\n", N, x, y, total, error, time);
        }
}