/*!
 *  \file       lock.cpp
 *  \brief
 *
 */


// #include "lock.hpp"

#include <mutex>

void task(std::mutex& mtx1, std::mutex& mtx2)
{
    std::unique_lock<std::mutex> lck1{mtx1, std::defer_lock_t};
    std::unique_lock<std::mutex> lck2{mtx2, std::defer_lock_t};
    try_lock(lck1, lck2);
}
