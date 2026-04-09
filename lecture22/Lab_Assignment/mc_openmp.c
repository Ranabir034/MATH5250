#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <num_samples> <num_threads>\n", argv[0]);
        return 1;
    }

    long N_total   = atol(argv[1]);
    int  N_threads = atoi(argv[2]);

    omp_set_num_threads(N_threads);

    long inside = 0;
    double t_start = omp_get_wtime();

    #pragma omp parallel reduction(+:inside)
    {
        int tid  = omp_get_thread_num();
        int nthr = omp_get_num_threads();

        unsigned int seed = 12345 + tid * 1000;

        long my_samples = N_total / nthr;

        for (long i = 0; i < my_samples; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (x*x + y*y <= 1.0)
                inside++;
        }
    }

    double elapsed = omp_get_wtime() - t_start;
    double pi = 4.0 * (double)inside / (double)N_total;

    printf("\n--- Monte Carlo pi (OpenMP) ---\n");
    printf("  Samples   : %ld\n",   N_total);
    printf("  Threads   : %d\n",    N_threads);
    printf("  Inside    : %ld\n",   inside);
    printf("  pi (est)  : %.8f\n",  pi);
    printf("  pi (true) : %.8f\n",  M_PI);
    printf("  error     : %.2e\n",  fabs(pi - M_PI));
    printf("  time      : %.4f s\n\n", elapsed);

    return 0;
}