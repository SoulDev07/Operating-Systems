#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define CHUNKSIZE 1
#define n 2
#define m 2

int main()
{
    int nthreads, tid, i, chunk;

    int a[5][5], b[5][5], c[5][5], j, k;

    printf("\n Enter the elements of first matrix ");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            scanf("\t%d", &a[i][j]);
    }

    printf("\n Enter the elements of second matrix ");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            scanf("\t%d", &b[i][j]);
    }

    printf("\n The elements of first matrix are");
    for (i = 0; i < m; i++)
    {
        printf("\n");
        for (j = 0; j < n; j++)
            printf("\t%d", a[i][j]);
    }

    printf("\n The elements of second matrix are");
    for (i = 0; i < m; i++)
    {
        printf("\n");
        for (j = 0; j < n; j++)
            printf("\t%d", b[i][j]);
    }

    chunk = CHUNKSIZE;

#pragma omp parallel private(i, tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("\nNumber of threads = %d\n", nthreads);
        }

        printf("\nThread %d starting...\n", tid);

#pragma omp for schedule(static, chunk)
        for (i = 0; i < m; i++)
        {
            printf("\n");
            for (j = 0; j < n; j++)
            {
                c[i][j] = 0;
                for (k = 0; k < m; k++)
                    c[i][j] += a[i][k] * b[k][j];
            }
        }

        printf("\n Multiplication of two matrices is");
        for (i = 0; i < m; i++)
        {
            printf("\n");
            for (j = 0; j < n; j++)
                printf("\t%d", c[i][j]);
        }
    }

    return 0;
}
