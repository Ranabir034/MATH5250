#include<stdio.h>
#include<math.h>

#include "node.h"

int main()
{
    const double a0 = 1.0;
    const double b0 = 2.0;
    const double tol = 1e-6;
    const int max_iter = 100;

    bisectionmethod(a0, b0, tol, max_iter);

    return 0;
}
