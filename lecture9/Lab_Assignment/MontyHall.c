#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void custom_Chebyshev(const int N, const int Npts, const double b[], const double x[], double *y)
{
    for (int i = 0; i < Npts; i++)
    {
        const double a = x[i];
        double phi;
        y[i] = b[0];

        switch (N)
        {
            case 5:
                phi = 16.0*pow(a,5) - 20.0*pow(a,3) + 5.0*a;
                y[i] += b[5] * phi;
            case 4:
                phi = 8.0*pow(a,4) - 8.0*pow(a,2) + 1.0;
                y[i] += b[4] * phi;
            case 3:
                phi = 4.0*pow(a,3) - 3.0*a;
                y[i] += b[3] * phi;
            case 2:
                phi = 2.0*pow(a,2) - 1.0;
                y[i] += b[2] * phi;
            case 1:
                phi = a;
                y[i] += b[1] * phi;
                break;
            case 0:
                break;
            default:
                printf("\n Error: degree out of range.\n");
                exit(1);

        }

    }
}


void writepoly(const int Npts, const double x[], const double y[])
{
    FILE *fp = fopen("Chebyshev.dat", "w");
    if (fp == NULL)
    {
        printf("\n Error: unable to open file.\n");
        exit(1);
    }

    for (int i = 0; i < Npts; i++)
    {
        fprintf(fp, "%lf %lf\n", x[i], y[i]);
    }

    fclose(fp);
}

int main()
{
    const int Nmax = 5;
    int N;

    printf("\n Input polynomial degree (0-%i): ", Nmax);
    scanf("%i", &N);
    if (N<0 || N>Nmax)
    {
        printf(" Invalid value N = %i.\n", N);
        printf(" N must satisfy: 0 <= N <= %i\n\n", Nmax);
        exit(1);
    }
    printf("\n");

    // read coefficients
    double b[Nmax + 1];
    for (int i = 0; i <= N; i++)
    {
        printf(" Set b[%i]: ", i);
        scanf("%lf", &b[i]);
    }

    printf("\n");

    // range of x-coordinates on [0,1]
    const int Npts = 201;
    double x[Npts];
    for (int i = 0; i < Npts; i++)
    {
        x[i] = (double)i/(Npts-1);
    }

    // evaluate polynomial
    double y[Npts];
    custom_Chebyshev(N, Npts, b, x, y);

    // write data to file
    writepoly(Npts, x, y);

    // call python to plot
    system("python3 PlotChebyshev.py");

    return 0;
    
}