/*!
 *  \file       thread_guard.cpp
 *  \brief
 *
 */


#include "ThreadGuard.hpp"


ThreadGuard::ThreadGuard(std::thread &thrd) : m_thread{thrd}
{
}

ThreadGuard::~ThreadGuard()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}
