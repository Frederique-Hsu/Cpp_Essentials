/*!
 *  \file       mutual_exclusion.hpp
 *  \brief      Study the mutex topic of multi-threading to avoid data race.
 *
 */



#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <vector>


/* Declaration ===================================================================================*/


template<typename Arg1, typename Arg2, typename Arg3>
void write(std::mutex count_mutex, Arg1 a1, Arg2 a2 = {}, Arg3 a3 = {});

void hello();
void world();

void composer();

class Work
{
};

void use_lock_guard(std::mutex& mtx, std::vector<std::string>& vs, int i);
void use_timed_lock();


/* Implementation ================================================================================*/
template<typename Arg1, typename Arg2, typename Arg3>
void write(std::mutex count_mutex, Arg1 a1, Arg2 a2, Arg3 a3)
{
    std::thread::id name = std::this_thread::get_id();

    count_mutex.lock();
    std::cout << "From thread " << name << " : "
              << a1 << ", "
              << a2 << ", "
              << a3;
    count_mutex.unlock();
}
