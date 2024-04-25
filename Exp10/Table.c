#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int i, t[N], f[N];

    omp_set_num_threads(2);

#pragma omp parallel sections private(i)
    {
#pragma omp section
        {
            printf("Table of Two\n");
            for (i = 1; i <= N; i++)
            {
                t[i] = i * 2;
                printf("Thread %d : %d\n", omp_get_thread_num(), t[i]);
            }
        }

#pragma omp section
        {
            printf("Table of Four\n");
            for (i = 1; i <= N; i++)
            {
                f[i] = i * 4;
                printf("Thread %d : %d\n", omp_get_thread_num(), f[i]);
            }
        }
    }

    return 0;
}
