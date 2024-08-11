/*!
 *  \file       parallel.c
 *  \brief
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    printf("number of available processors = %d\n", omp_get_num_procs());
    printf("number of threads = %d\n", omp_get_max_threads());

    long n = atol(argv[1]);
    printf("we will form sum of numbers from 1 to %ld\n", n);

    double start = omp_get_wtime();

    unsigned long long sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (long i = 0; i < n; ++i)
    {
        sum += i;
    }

    double end = omp_get_wtime();

    printf("Sum = %llu\n", sum);
    printf("Elapsed wall clock time = %f seconds\n", end-start);

    return EXIT_SUCCESS;
}