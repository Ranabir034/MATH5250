#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "node.h"

void bisectionmethod(const double a0, const double b0, const double tol, const int max_iter)
{
    double fa = f(a0);
    double fb = f(b0);

    if (fa*fb>=0.0)
    {
        printf("\n Error: f(a) and f(b) should have opposite signs.\n");
        return;
    }
    printf("\n Bisection method:\n");
    printf(" f(x) = x^3 - x - 2\n");
    printf("Initial interval: [%.6f, %.6f]\n", a0, b0);
    printf("Tolerance: %.6f\n", tol);
    printf("Maximum iterations: %d\n", max_iter);

    node* top = NULL;

    double a = a0;
    double b = b0;
    int iter = 0;
    double midpoint, f_mid;

    while (iter<max_iter)
    {
        iter++;
        midpoint = (a+b)/2.0;
        f_mid = f(midpoint);
        push(iter, a, b, midpoint, f_mid, &top);

        if (fabs(f_mid)<tol || (b-a)*0.5 <tol)
        {
            printf("Convergence achieved after %d iterations.\n", iter);
            printf("Approximate root: %.6f\n", midpoint);
            printf("f(%.6f) = %.6f\n", midpoint, f_mid);
            break;
        }

        if (fa*f_mid<0.0)
        {
            b = midpoint;
            fb = f_mid;
        }
        else
        {
            a = midpoint;
            fa = f_mid;
        }

        if (iter==max_iter)
        {
            printf("Maximum iterations reached without convergence.\n");
            printf("Last midpoint: %.6f\n", midpoint);
            printf("f(%.6f) = %.6f\n", midpoint, f_mid);
        }
    }

    printf("\n Bisection method iterations:\n");
    displaystack(top);
    deletestack(&top);
}