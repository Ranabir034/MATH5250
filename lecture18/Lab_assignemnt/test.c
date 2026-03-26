/*
 * European Call Option Pricing via Simpson's Rule + OpenMP
 * Compared against the Black-Scholes closed-form solution.
 *
 * Usage: ./option <num_threads> <N>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// option parameters
static const double S0    = 100.0;
static const double K     = 100.0;
static const double R     = 0.05;
static const double T     = 1.0;
static const double SIGMA = 0.2;

// upper limit of integration
static const double S_MAX = 500.0;  

// lognormal PDF of the asset price at maturity 
static double pdf(double S)
{
    double mu  = log(S0) + (R - 0.5*SIGMA*SIGMA) * T;
    double sig = SIGMA * sqrt(T);                     /* sigma * sqrt(T) */
    double z   = (log(S) - mu) / sig;
    return exp(-0.5*z*z) / (S * sig * sqrt(2.0*M_PI));
}

/* ── integrand: (S - K) * p(S)  over [K, S_max] ─────────────────── */
static double integrand(double S)
{
    return (S - K) * pdf(S);
}

static double simpson(int N, int nthreads)
{
    // even number of intervels required for Simpson's rule
    if (N % 2 != 0) {
        N++;
        printf("  [note] N adjusted to %d (must be even for Simpson)\n", N);
    }

    double a = K;
    double b = S_MAX;
    double h = (b - a) / (double)N;

    double sum = integrand(a) + integrand(b);

    // parallelize the loop with OpenMP
    #pragma omp parallel for num_threads(nthreads) \
            reduction(+: sum) schedule(static)
    for (int i = 1; i < N; i++)
    {
        double S = a + i * h;
        double w = (i % 2 == 1) ? 4.0 : 2.0;   /* 4 if odd, 2 if even */
        sum += w * integrand(S);
    }

    return (h / 3.0) * sum;
}

static double black_scholes()
{
    double sqrtT = sqrt(T);
    double d1 = (log(S0/K) + (R + 0.5*SIGMA*SIGMA)*T) / (SIGMA * sqrtT);
    double d2 = d1 - SIGMA * sqrtT;

    double Phi_d1 = 0.5 * (1.0 + erf(d1 / sqrt(2.0)));
    double Phi_d2 = 0.5 * (1.0 + erf(d2 / sqrt(2.0)));

    return S0 * Phi_d1 - K * exp(-R * T) * Phi_d2;
}


//main program 
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s <num_threads> <N>\n", argv[0]);
        fprintf(stderr, "  num_threads : positive integer\n");
        fprintf(stderr, "  N           : number of integration intervals (even)\n");
        return 1;
    }

    int nthreads = atoi(argv[1]);
    int N        = atoi(argv[2]);

    if (nthreads < 1 || N < 2) {
        fprintf(stderr, "error: need nthreads >= 1 and N >= 2\n");
        return 1;
    }

    /* ── numerical integration (timed) ──────────────────────────── */
    double t1       = omp_get_wtime();
    double integral = simpson(N, nthreads);
    double C_num    = exp(-R * T) * integral;
    double t2       = omp_get_wtime();

    /* ── Black-Scholes exact answer ──────────────────────────────── */
    double C_bs = black_scholes();

    /* ── print results ───────────────────────────────────────────── */
    printf("\n");
    printf("  Threads     : %d\n",       nthreads);
    printf("  N           : %d\n",       N);
    printf("  Simpson C   : %.10f\n",    C_num);
    printf("  B-S exact C : %.10f\n",    C_bs);
    printf("  |Error|     : %.6e\n",     fabs(C_num - C_bs));
    printf("  Wall time   : %.6e s\n\n", t2 - t1);

    return 0;
}