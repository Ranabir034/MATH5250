#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"
#include "trimatrix.h"

void Hessenberg(const matrix* Ain, trimatrix* T);
void QRA(trimatrix* T);

/* Build the N x N tridiagonal matrix with 2 on diagonal, -1 on off-diagonals
   (same matrix used in previous eigenvalue assignment) */
matrix build_test_matrix(int N)
{
    matrix A = new_matrix(N, N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            mget(A, i, j) = 2.0*(i == j) - 1.0*(abs(i-j) == 1);
    return A;
}

int main()
{
    int sizes[2] = {6, 12};

    for (int s = 0; s < 2; s++)
    {
        int N = sizes[s];
        printf("==========================================\n");
        printf("  N = %d\n", N);
        printf("==========================================\n");

        matrix A = build_test_matrix(N);

        printf("\nOriginal Matrix A:\n");
        print_matrix(&A);

        /* Phase 1: Hessenberg (tridiagonal) reduction */
        trimatrix T = new_trimatrix(N);
        Hessenberg(&A, &T);

        printf("After Hessenberg reduction to tridiagonal form T:\n");
        print_trimatrix(&T);

        /* Phase 2: QR algorithm to reveal eigenvalues */
        QRA(&T);

        printf("After QR Algorithm (diagonal = eigenvalues):\n");
        print_trimatrix(&T);

        /* Print eigenvalues and compare to analytical values */
        printf("Computed eigenvalues (diagonal entries of T):\n");
        for (int i = 1; i <= N; i++)
            printf("  lambda_%d = %18.10f\n", i, tget(&T, i, i));

        printf("\nAnalytical eigenvalues: lambda_k = 2 - 2*cos(k*pi/%d)\n", N+1);
        for (int k = 1; k <= N; k++)
            printf("  lambda_%d = %18.10f\n", k, 2.0 - 2.0*cos(k * M_PI / (N+1)));

        delete_trimatrix(&T);
        delete_matrix(&A);
        printf("\n");
    }

    return 0;
}