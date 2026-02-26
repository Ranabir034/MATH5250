#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    double x;
    double y;

    int nfactorial = 1;
    double exp_result;
    double log_result;

    // get user input
    printf("Enter an integer for factorial computation: ");
    scanf("%d", &n);
    printf("Enter a real number for exponential computation: ");
    scanf("%lf", &x);
    printf("Enter a real number for logarithm computation: ");
    scanf("%lf", &y);

    for (int i = 1; i <= n; i++)
    {
        nfactorial = nfactorial * i;
    }

    exp_result = exp(x);
    log_result = log(y);

    printf("\n");
    printf("======================================\n");
    printf("Mathematical Computations\n");
    printf("======================================\n");
    printf("Factorial of %d = %d\n", n, nfactorial);
    printf("Exponential of %.4f = %.6f\n", x, exp_result);
    printf("Logarithm of %.4f = %.6f\n", y, log_result);
    printf("======================================\n");
    printf("\n");

    return 0;

}