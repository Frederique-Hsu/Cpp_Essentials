/*!
 *  \file   resource_management.cpp
 *  \brief  
 *  
 */


#include "Vector.hpp"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <exception>

#include <gtest/gtest.h>

/* Prototypes ====================================================================================*/
CopyMove::Vector init(int n, std::vector<std::thread>& threads);
void heartbeat();


/* Global objects ================================================================================*/



/* Implementations ===============================================================================*/
void heartbeat()
{
    using namespace std::chrono_literals;

    auto start_time = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1000ms);
    auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

    std::cout << "I'm beating every " << elapsed_time.count() << "ms." << std::endl;
}

CopyMove::Vector init(int n, std::vector<std::thread>& threads)
{
    std::thread t{heartbeat};
    threads.push_back(std::move(t));

    CopyMove::Vector vec(n);
    for (int i = 0; i < vec.size(); ++i)
    {
        vec[i] = 577;
    }
    return vec;
}


/* Unit Testing ==================================================================================*/
TEST(UTester4ResourceManagement, DISABLED_CheckMoveConstructorManageObjectsScope)
{
    try
    {
        std::vector<std::thread> my_threads;

        auto vec = init(10000, my_threads);
    }
    catch (std::exception& except)
    {
        std::cout << except.what() << std::endl;
    }
}
