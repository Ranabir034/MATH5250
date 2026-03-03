#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

static double randn(void)
{
    double u1, u2;
    do { u1 = (double)rand() / RAND_MAX; } while (u1 == 0.0);
    u2 = (double)rand() / RAND_MAX;
    return sqrt(-2.0*log(u1)) * cos(2.0*3.14159265358979323846*u2);
}

matrix build_blur_matrix(int n)
{
    matrix A = new_matrix(n, n);
    for (int i = 1; i <= n; i++) {
        mget(A, i, i) = 0.5;
        if (i > 1) mget(A, i, i-1) = 0.25;
        if (i < n) mget(A, i, i+1) = 0.25;
    }
    return A;
}

vector build_true_signal(int n)
{
    vector x = new_vector(n);
    for (int i = 1; i <= n; i++)
        vget(x, i) = ((i >= n/4) && (i <= n/2)) ? 1.0 : 0.0;
    return x;
}

double relative_error(const vector* x, const vector* xr)
{
    vector d = vector_sub(x, xr);
    double e = vector_norm(&d) / vector_norm(x);
    free_vector(&d);
    return e;
}

vector tikhonov_solve(const matrix* A, const vector* bn, double lam)
{
    int n = A->rows;
    matrix AT  = matrix_transpose(A);
    matrix ATA = matrix_mult(&AT, A);
    for (int i = 1; i <= n; i++) mget(ATA, i, i) += lam;
    vector ATb = matrix_vector_mult(&AT, bn);
    vector xr  = solve(&ATA, &ATb);
    free_matrix(&AT); free_matrix(&ATA); free_vector(&ATb);
    return xr;
}

void run_experiment(int n)
{
    printf("\n==========================================================\n");
    printf("  n = %d\n", n);
    printf("==========================================================\n");
    printf("  %-10s | %-18s | %-18s %-18s %-18s\n",
           "sigma","Direct err","Tikh lam=1e-6","Tikh lam=1e-4","Tikh lam=1e-2");
    printf("  -----------|--------------------|-----------");
    printf("--------------------------------------------------\n");

    matrix A      = build_blur_matrix(n);
    vector xtrue  = build_true_signal(n);
    vector bclean = matrix_vector_mult(&A, &xtrue);

    double sigmas[3]  = {1e-6, 1e-4, 1e-2};
    double lambdas[3] = {1e-6, 1e-4, 1e-2};

    for (int si = 0; si < 3; si++) {
        double sigma = sigmas[si];
        vector bn = new_vector(n);
        for (int i = 1; i <= n; i++)
            vget(bn, i) = vget(bclean, i) + sigma*randn();

        vector xd  = solve(&A, &bn);
        double ed  = relative_error(&xtrue, &xd);

        double et[3];
        for (int li = 0; li < 3; li++) {
            vector xt = tikhonov_solve(&A, &bn, lambdas[li]);
            et[li]    = relative_error(&xtrue, &xt);
            free_vector(&xt);
        }
        printf("  %-10.1e | %-18.6e | %-18.6e %-18.6e %-18.6e\n",
               sigma, ed, et[0], et[1], et[2]);
        free_vector(&bn); free_vector(&xd);
    }
    printf("\n");
    free_matrix(&A); free_vector(&xtrue); free_vector(&bclean);
}

int main(void)
{
    srand(42);
    printf("\n*************************************************************\n");
    printf("*  1D Imaging Deblurring  (MATH 5250 Lab)                   *\n");
    printf("*************************************************************\n");
    printf("  Blur : b_i = (x_{i-1}+2x_i+x_{i+1})/4, zero BC\n");
    printf("  Signal: x_i=1 for n/4<=i<=n/2, else 0\n");
    printf("  Direct solve: A x_rec = b+eps\n");
    printf("  Tikhonov   : (A^T A + lam I) x_rec = A^T(b+eps)\n");
    run_experiment(64);
    run_experiment(128);
    return 0;
}