/*!
 *  \file       test_multi_threads_calc.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <thread>
#include <chrono>

#include "calc.hpp"

TEST(UTester4Calc, CheckHowToReturnResultFromThread)
{
    std::vector<int>  odd_vec{1, 3, 5, 7,  9, 11, 13, 15, 17, 19};
    std::vector<int> even_vec{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    int odd_numbers_sum, even_numbers_sum;

    std::thread calculate_odd_numbers_sum(calculate, odd_vec, &odd_numbers_sum);
    std::thread calculate_even_numbers_sum(Calculator{even_vec, &even_numbers_sum});

    calculate_odd_numbers_sum.join();
    calculate_even_numbers_sum.join();

    EXPECT_EQ(odd_numbers_sum, 100);
    EXPECT_EQ(even_numbers_sum, 110);
}


TEST(UTester4WaitEvent, CheckWaitEventFinished)
{
    using namespace std;
    using namespace std::chrono;

    auto t1 = high_resolution_clock::now();
    this_thread::sleep_for(milliseconds(20));
    auto t2 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(t2 - t1).count() << " nanoseconds passed." << std::endl;
}

TEST(UTester4MultiThreads, CheckSupportedThreads)
{
    auto num = std::thread::hardware_concurrency();
    std::cout << "Current machine supports " << num << " threads running in parallel." << std::endl;

    std::cout << "Current thread id = " << std::this_thread::get_id() << std::endl;

    std::thread mythread{};
    std::cout << "My thread's ID = " << mythread.get_id() << std::endl;
}
