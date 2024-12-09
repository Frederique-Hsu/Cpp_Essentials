/*!
 *  \file       test_threads_safety.cc
 *  \brief      
 *  
 */


#include <gtest/gtest.h>
#include <thread>

#include "my_thread.hpp"

TEST(UTest4ThreadsSafety, CheckMyThreadWorksWell)
{
    MyThread thrdObj(3, 4);
    std::thread task(&MyThread::run, &thrdObj);

    /*!
     *  \remark waiting for the thread to finish the run() function, 
     *          namely the addition calculation.
     */
    while ((!thrdObj.is_ready) || (!thrdObj.is_done))
    {
    }

    EXPECT_EQ(thrdObj.getResult(), 3 + 4);
    task.join();
}

TEST(UTest4ThreadsSafety, CheckImprovedThread)
{
    MyImprovedThread thrdObj(3, 4);
    std::thread task(&MyImprovedThread::run, &thrdObj);

    EXPECT_EQ(thrdObj.getResult(), 3 + 4);
    task.join();
}

TEST(UTest4ThreadsSafety, CheckThreadSafeFunctions)
{
    std::atomic<int> shared_counter(0);
    std::mutex io_mutex;

    auto ThreadSafeFunction = [&shared_counter, &io_mutex](int increment)
    {
        for (int i = 0; i < increment; ++i)
        {
            ++shared_counter;

            std::lock_guard<std::mutex> lock(io_mutex);
        }
    };

    auto WaitForThreads = [](std::vector<std::thread>& threads)
    {
        for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    };

    const int num_threads = 10;
    const int increment_per_thread = 100;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(std::thread(ThreadSafeFunction, increment_per_thread));
    }
    WaitForThreads(threads);

    EXPECT_EQ(shared_counter.load(), num_threads * increment_per_thread);
}