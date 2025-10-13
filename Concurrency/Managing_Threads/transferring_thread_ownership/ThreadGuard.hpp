/*!
 *  \file       ThreadGuard.hpp
 *  \brief
 *
 */


#pragma once


#include <thread>


class ThreadGuard
{
public:
    explicit ThreadGuard(std::thread &thrd);
    ~ThreadGuard();
    ThreadGuard(const ThreadGuard &) = delete;
    ThreadGuard& operator=(const ThreadGuard &) = delete;

private:
    std::thread &m_thread;
};
