#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100000000L

/* fill x with a simple sine wave */
void fill(double *x) {
    for (long i = 0; i < N; i++)
        x[i] = sin(2.0 * M_PI * i / N) + 0.5 * cos(6.0 * M_PI * i / N);
}

/* ── FINE-GRAIN ─────────────────────────────────────────── */

void fine_2norm(double *x, int nt) {
    double sq = 0.0;
    #pragma omp parallel for num_threads(nt) reduction(+:sq)
    for (long i = 0; i < N; i++) sq += x[i] * x[i];
    double norm = sqrt(sq);
    #pragma omp parallel for num_threads(nt)
    for (long i = 0; i < N; i++) x[i] /= norm;
}

void fine_maxnorm(double *x, int nt) {
    double mx = 0.0;
    #pragma omp parallel for num_threads(nt) reduction(max:mx)
    for (long i = 0; i < N; i++) if (fabs(x[i]) > mx) mx = fabs(x[i]);
    #pragma omp parallel for num_threads(nt)
    for (long i = 0; i < N; i++) x[i] /= mx;
}

/* ── COARSE-GRAIN ───────────────────────────────────────── */

void coarse_2norm(double *x, int nt) {
    double sq = 0.0;
    #pragma omp parallel num_threads(nt)
    {
        int t = omp_get_thread_num(), tc = omp_get_num_threads();
        long lo = (long)t * (N / tc);
        long hi = (t == tc - 1) ? N : lo + N / tc;

        double local = 0.0;
        for (long i = lo; i < hi; i++) local += x[i] * x[i];
        #pragma omp critical
        sq += local;
        #pragma omp barrier

        double norm = sqrt(sq);
        for (long i = lo; i < hi; i++) x[i] /= norm;
    }
}

void coarse_maxnorm(double *x, int nt) {
    double mx = 0.0;
    #pragma omp parallel num_threads(nt)
    {
        int t = omp_get_thread_num(), tc = omp_get_num_threads();
        long lo = (long)t * (N / tc);
        long hi = (t == tc - 1) ? N : lo + N / tc;

        double local = 0.0;
        for (long i = lo; i < hi; i++) if (fabs(x[i]) > local) local = fabs(x[i]);
        #pragma omp critical
        if (local > mx) mx = local;
        #pragma omp barrier

        for (long i = lo; i < hi; i++) x[i] /= mx;
    }
}

/* ── HELPERS ────────────────────────────────────────────── */

void verify(double *x) {
    double sq = 0.0, mx = 0.0;
    for (long i = 0; i < N; i++) { sq += x[i]*x[i]; if (fabs(x[i]) > mx) mx = fabs(x[i]); }
    printf("  check -> 2-norm=%.6f  max-norm=%.6f\n", sqrt(sq), mx);
}

void sweep(const char *label, void (*fn)(double *, int), double *x) {
    int threads[] = {1, 2, 4, 8, 16};
    printf("\n%s\n", label);
    printf("  Threads  Time(s)  Speedup\n");
    double tref = 0.0;
    for (int k = 0; k < 5; k++) {
        fill(x);
        double t1 = omp_get_wtime();
        fn(x, threads[k]);
        double elapsed = omp_get_wtime() - t1;
        if (k == 0) { tref = elapsed; verify(x); }
        printf("  %-7d  %-7.4f  %.4f\n", threads[k], elapsed, tref / elapsed);
    }
}

/* ── MAIN ───────────────────────────────────────────────── */

int main(void) {
    double *x = malloc(N * sizeof(double));

    printf("Signal normalization  (N = %ld)\n", N);

    sweep("Fine-grain   |  2-norm",   fine_2norm,     x);
    sweep("Fine-grain   |  Max-norm", fine_maxnorm,   x);
    sweep("Coarse-grain |  2-norm",   coarse_2norm,   x);
    sweep("Coarse-grain |  Max-norm", coarse_maxnorm, x);

    free(x);
    return 0;
}