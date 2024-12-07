/*!
 *  \file       test_parallel_accumulate.c++
 *  \brief      carry out the unit testing for \code UTester4ParallelAccumulator
 *
 */


#include "test_parallel_accumulate.h++"
#include "multi_threads.hpp"

#include <random>
#include <chrono>

UTester4ParallelAccumulator::UTester4ParallelAccumulator()
{
    random_numbers.resize(4e06);

    EXPECT_EQ(random_numbers.size(), 4e06);
}


void UTester4ParallelAccumulator::SetUp()
{
    std::srand(std::time(NULL));

    for (std::size_t index = 0; index < random_numbers.size(); ++index)
    {
        std::uint64_t random_number = std::rand() % 1000000UL;
        random_numbers[index] = random_number;
    }
}

void UTester4ParallelAccumulator::TearDown()
{
    random_numbers.clear();

    EXPECT_EQ(random_numbers.empty(), true);
}

TEST_F(UTester4ParallelAccumulator, CheckParallelAccumulate)
{
    using namespace std::chrono;

    /* Calculate the element-wise accumulated sum by a for-loop */
    double element_wise_accumulated_sum = 0.0;
    auto start_timestamp = high_resolution_clock::now();
    for (auto element : random_numbers)
    {
        element_wise_accumulated_sum += element;
    }
    auto stop_timestamp = high_resolution_clock::now();
    std::cout << std::endl
              << "The element-wise accumulated sum is: " << element_wise_accumulated_sum << "\n"
              << "The for-loop has consumed "
              << duration_cast<microseconds>(stop_timestamp - start_timestamp).count()
              << " micro-seconds.\n" << std::endl;
    /*============================================================================================*/

    auto begin_pointer = random_numbers.begin().base();
    auto end_pointer = random_numbers.end().base();

    /* Calculate the sum of all the elements of a vector in serial */
    start_timestamp = high_resolution_clock::now();
    double serial_sum = accum(begin_pointer, end_pointer, 0.0);
    stop_timestamp = high_resolution_clock::now();
    std::cout << "The serial sum is: " << serial_sum << "\n"
              << "accum() has consumed "
              << duration_cast<microseconds>(stop_timestamp - start_timestamp).count()
              << " micro-seconds.\n" << std::endl;
    /*============================================================================================*/

    /*Calculate the sum of all the elements of a vector in parallel */
    start_timestamp = high_resolution_clock::now();
    double parallel_sum = dual_tasks_parallel_compute(random_numbers);
    stop_timestamp = high_resolution_clock::now();
    std::cout << "The parallel sum is: " << parallel_sum << "\n"
              << "dual_tasks_parallel_compute() has consumed "
              << duration_cast<microseconds>(stop_timestamp - start_timestamp).count()
              << " micro-seconds.\n" << std::endl;
    /*============================================================================================*/

    /* Calculate the sum of all the elements of a vector asynchronously */
    start_timestamp = high_resolution_clock::now();
    double async_sum = quad_tasks_async_compute(random_numbers);
    stop_timestamp = high_resolution_clock::now();
    std::cout << "The async sum is " << async_sum << "\n"
              << "quad_tasks_async_compute() has consumed "
              << duration_cast<microseconds>(stop_timestamp - start_timestamp).count()
              << " micro-seconds.\n" << std::endl;
    /*============================================================================================*/

    EXPECT_DOUBLE_EQ(element_wise_accumulated_sum, serial_sum);
    EXPECT_DOUBLE_EQ(serial_sum, parallel_sum);
    EXPECT_DOUBLE_EQ(parallel_sum, async_sum);
}
