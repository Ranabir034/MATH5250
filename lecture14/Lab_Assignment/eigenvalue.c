#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"

/* ============================================================
   1. POWER ITERATION
   Finds the largest eigenvalue (by magnitude).
   ============================================================ */
double power_iteration(const matrix* A,
                       const vector* v0,
                       double TOL, int MaxIters)
{
    double norm0  = vector_norm(v0);
    vector v      = vector_scale(v0, 1.0/norm0);
    double lambda = rayleigh_quotient(A, &v);
    double lambda_old;

    printf("  --- Power Iteration ---\n");
    printf("  %4s | %18s | %14s\n", "k", "lambda_k", "|delta lambda|");
    printf("  -----|--------------------|--------------\n");
    printf("  %4d | %18.10f |      --\n", 0, lambda);

    int k = 0, mstop = 0;
    while (!mstop) {
        k++;
        vector w     = matrix_vector_mult(A, &v);
        double normw = vector_norm(&w);
        free(v.val);
        v          = vector_scale(&w, 1.0/normw);
        free(w.val);
        lambda_old = lambda;
        lambda     = rayleigh_quotient(A, &v);

        printf("  %4d | %18.10f | %14.6e\n", k, lambda, fabs(lambda - lambda_old));

        if (fabs(lambda - lambda_old) < TOL || k == MaxIters)
            mstop = 1;
    }
    printf("  Converged in %d iterations.\n", k);

    free(v.val);
    return lambda;
}

/* ============================================================
   2. SHIFTED INVERSE POWER ITERATION
   Finds the eigenvalue closest to shift mu.
   ============================================================ */
double shifted_inverse_iteration(const matrix* A,
                                 const vector* v0,
                                 double mu,
                                 double TOL, int MaxIters)
{
    int n = A->rows;

    /* Build (A - mu*I) */
    matrix AmuI = new_matrix(n, n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            mgetp(&AmuI,i,j) = mgetp(A,i,j);
            if (i == j) mgetp(&AmuI,i,j) -= mu;
        }

    double norm0  = vector_norm(v0);
    vector v      = vector_scale(v0, 1.0/norm0);
    double lambda = rayleigh_quotient(A, &v);
    double lambda_old;

    printf("  --- Shifted Inverse Power Iteration (mu = %.4f) ---\n", mu);
    printf("  %4s | %18s | %14s\n", "k", "lambda_k", "|delta lambda|");
    printf("  -----|--------------------|--------------\n");
    printf("  %4d | %18.10f |      --\n", 0, lambda);

    int k = 0, mstop = 0;
    while (!mstop) {
        k++;
        vector w     = solve(&AmuI, &v);
        double normw = vector_norm(&w);
        free(v.val);
        v          = vector_scale(&w, 1.0/normw);
        free(w.val);
        lambda_old = lambda;
        lambda     = rayleigh_quotient(A, &v);

        printf("  %4d | %18.10f | %14.6e\n", k, lambda, fabs(lambda - lambda_old));

        if (fabs(lambda - lambda_old) < TOL || k == MaxIters)
            mstop = 1;
    }
    printf("  Converged in %d iterations.\n", k);

    free(v.val);
    free(AmuI.val);
    return lambda;
}

/* ============================================================
   3. RAYLEIGH QUOTIENT ITERATION
   Finds an eigenvalue near the initial guess (cubic convergence).
   ============================================================ */
double rayleigh_quotient_iteration(const matrix* A,
                                   const vector* v0,
                                   double TOL, int MaxIters)
{
    int n = A->rows;

    double norm0  = vector_norm(v0);
    vector v      = vector_scale(v0, 1.0/norm0);
    double lambda = rayleigh_quotient(A, &v);
    double lambda_old;

    printf("  --- Rayleigh Quotient Iteration ---\n");
    printf("  %4s | %18s | %14s\n", "k", "lambda_k", "|delta lambda|");
    printf("  -----|--------------------|--------------\n");
    printf("  %4d | %18.10f |      --\n", 0, lambda);

    int k = 0, mstop = 0;
    while (!mstop) {
        k++;
        matrix AlamI = new_matrix(n, n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                mgetp(&AlamI,i,j) = mgetp(A,i,j);
                if (i == j) mgetp(&AlamI,i,j) -= lambda;
            }
        vector w     = solve(&AlamI, &v);
        double normw = vector_norm(&w);
        free(AlamI.val);
        free(v.val);
        v          = vector_scale(&w, 1.0/normw);
        free(w.val);
        lambda_old = lambda;
        lambda     = rayleigh_quotient(A, &v);

        printf("  %4d | %18.10f | %14.6e\n", k, lambda, fabs(lambda - lambda_old));

        if (fabs(lambda - lambda_old) < TOL || k == MaxIters)
            mstop = 1;
    }
    printf("  Converged in %d iterations.\n", k);

    free(v.val);
    return lambda;
}

/* ============================================================
   MAIN
   ============================================================ */
int main()
{
    const int n = 5;

    /* tridiagonal matrix: diag(2), off-diag(-1) */
    matrix A = new_matrix(n, n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mget(A,i,j) = 2.0*(i==j) - 1.0*(i-1==j) - 1.0*(j-1==i);

    printf("Test matrix A:\n");
    print_matrix_full(&A, "A");

    double TOL      = 1e-10;
    int    MaxIters = 200;

    /* initial guess: all ones */
    vector v0 = new_vector(n);
    for (int i = 1; i <= n; i++) vget(v0,i) = 1.0;

    printf("\n");

    /* 1. power Iteration -> largest eigenvalue */
    double lam_max = power_iteration(&A, &v0, TOL, MaxIters);

    printf("\n");

    /* 2. shifted Inverse -> smallest eigenvalue (shift mu = 0.2, near lambda_1) */
    double lam_min = shifted_inverse_iteration(&A, &v0, 0.2, TOL, MaxIters);

    printf("\n");

    /* 3. rayleigh Quotient -> middle eigenvalue
       initial guess [1,0,-1,0,1] matches the shape of the lambda_3 eigenvector */
    vector v_mid = new_vector(n);
    vget(v_mid,1)= 1.0; vget(v_mid,2)= 0.0; vget(v_mid,3)=-1.0;
    vget(v_mid,4)= 0.0; vget(v_mid,5)= 1.0;
    double lam_mid = rayleigh_quotient_iteration(&A, &v_mid, TOL, MaxIters);
    free(v_mid.val);

    /* summary */
    printf("\n========================================\n");
    printf("  COMPUTED EIGENVALUES\n");
    printf("========================================\n");
    printf("  Power Iteration   (largest) : %.10f\n", lam_max);
    printf("  Shifted Inverse   (smallest): %.10f\n", lam_min);
    printf("  Rayleigh Quotient (middle)  : %.10f\n", lam_mid);

    printf("\n  Analytical: lambda_k = 2 - 2*cos(k*pi/%d)\n", n+1);
    for (int k = 1; k <= n; k++)
        printf("  lambda_%d = %.10f\n", k, 2.0 - 2.0*cos(k*M_PI/(n+1)));

    free(A.val);
    free(v0.val);
    return 0;
}