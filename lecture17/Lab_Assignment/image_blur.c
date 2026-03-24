/*
 * Lab Assignment: Image Blurring with OpenMP
 * Usage: ./blur.exe <thread_count> <N>
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define N_MAX 10000

static int img[N_MAX][N_MAX];
static int blurred[N_MAX][N_MAX];

/* Save grayscale image as PPM — opens in Preview on Mac, any viewer on Linux */
void save_image(const char *filename, int data[N_MAX][N_MAX], int rows, int cols)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "P3\n%d %d\n255\n", cols, rows);   /* PPM header */
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fprintf(fp, "%d %d %d\n", data[i][j], data[i][j], data[i][j]);
    fclose(fp);
    printf("Saved: %s\n", filename);
}

int main(int argc, char *argv[])
{
    int thread_count = atoi(argv[1]);
    int N            = atoi(argv[2]);

    /* Fill image with random values 0-255 */
    srand(42);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            img[i][j] = rand() % 256;

    /* Apply 3x3 average blur */
    double t1 = omp_get_wtime();

    #pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i < N-1; i++)
        for (int j = 1; j < N-1; j++)
            blurred[i][j] = (img[i-1][j-1] + img[i-1][j] + img[i-1][j+1]
                           + img[i  ][j-1] + img[i  ][j] + img[i  ][j+1]
                           + img[i+1][j-1] + img[i+1][j] + img[i+1][j+1]) / 9;

    double t2 = omp_get_wtime();

    printf("Threads = %d | N = %d | Walltime = %.6e sec\n", thread_count, N, t2 - t1);

    save_image("original.ppm", img,     N,   N  );
    save_image("blurred.ppm",  blurred, N-2, N-2);

    return 0;
}