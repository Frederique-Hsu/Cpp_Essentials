/*!
 *  \file       parallel_main.cpp
 *  \brief
 *
 */


#include <iostream>
#include <omp.h>


int main(int argc, char* argv[])
{
    std::cout << "number of available processors: " << omp_get_num_procs() << std::endl;
    std::cout << "number of threads: " << omp_get_max_threads() << std::endl;

    auto n = std::stol(argv[1]);
    std::cout << "we will form sum of numbers from 1 to " << n << std::endl;

    // start timer
    auto start = omp_get_wtime();

    auto sum = 0LL;
#pragma omp parallel for reduction(+ : sum)
    for (auto i = 1; i <= n; ++i)
    {
        sum += i;
    }

    // stop timer
    auto end = omp_get_wtime();

    std::cout << "sum = " << sum << std::endl;
    std::cout << "elapsed wall clock time: " << end - start << " seconds" << std::endl;

    return 0;
}