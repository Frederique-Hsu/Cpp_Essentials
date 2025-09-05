/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include "accumulate.hpp"

#include <chrono>
#include <cassert>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    unsigned numbers[1000];
    auto fillNumbers = [&numbers]()
    {
        for (unsigned i = 0; i < sizeof(numbers)/sizeof(numbers[0]); ++i)
        {
            numbers[i] = i+1;
        }
    };
    fillNumbers();

    auto start1 = std::chrono::high_resolution_clock::now();
    std::uint64_t serial_sum = 0;
    for (unsigned i = 0; i < sizeof(numbers)/sizeof(numbers[0]); ++i)
    {
        serial_sum += numbers[i];
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    auto serial_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();
    std::cout << "serial_duration_ns = " << serial_duration_ns << "ns" << std::endl;


    auto start2 = std::chrono::high_resolution_clock::now();
    std::uint64_t parallel_sum = 0;
    parallel_sum = parallel_accumulate(std::begin(numbers), std::end(numbers), 0);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto parallel_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
    std::cout << "parallel_duration_ns = " << parallel_duration_ns << "ns" << std::endl;

    if (serial_sum == parallel_sum)
    {
        std::cout << "OK!" << std::endl;
    }

    return 0;
}
