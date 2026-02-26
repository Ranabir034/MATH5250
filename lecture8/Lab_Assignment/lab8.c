#include <stdio.h>
#include <math.h>

int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
    
}

double custom_exp(double x)
{
    const double e = 2.718281828459;
    int x0 = (int)round(x);
    double dx = x - x0;
    int N = 20;
    // double exp_x0=0.0;
    double sum_dx = 0.0;

    for (int k = 0; k <= N; k++)
    {
        sum_dx += pow(dx, k) / (double)factorial(k);
    }   
    // double exp_x0 = pow(e, x0);

    // return exp_x0 * sum;

    double e_approx = 0.0;
    for (int k = 0; k <= N; k++)
    {
        e_approx += 1.0 / (double)factorial(k);
    }

    double exp_x0=pow(e_approx, x0);
    return exp_x0 * sum_dx;
}

int main()
{
    int npts = 51;
    double x_arr[npts];
    double my_exp_arr[npts];
    double lib_exp_arr[npts];

    for (int i = 0; i < npts; i++)
    {
        x_arr[i] = i * 0.02; // x = 0, 0.02, ..., 1.0
        my_exp_arr[i] = custom_exp(x_arr[i]);
        lib_exp_arr[i] = exp(x_arr[i]);

        printf("%f %f %f\n", x_arr[i], my_exp_arr[i], lib_exp_arr[i]);

    }

    printf("\n");
    printf("=*60");
    printf("\n");

    FILE *outfile = fopen("lab8_output.dat", "w");
    if (outfile ==NULL)
    {
        printf("Error opening file for writing.\n");
        return 1;
    }

    fprintf(outfile, "x\tcustom_exp(x)\tlib_exp(x)\n");
    for (int i = 0; i < npts; i++)
    {
        fprintf(outfile, "%f\t%f\t%f\n", x_arr[i], my_exp_arr[i], lib_exp_arr[i]);
    }   

    fclose(outfile);

    printf("Data written to lab8_output.dat\n");

    // int num = 5;
    // printf("Factorial of %d is %d\n", num, factorial(num));

    // double x = 5.3;
    // printf("Custom exp(%f) = %f\n", x, custom_exp(x));

    return 0;
}


