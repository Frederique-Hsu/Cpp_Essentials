/*!
 *  \file       ScopedThread.hpp
 *  \brief
 *
 */


#pragma once

#include <thread>


class ScopedThread
{
private:
    std::thread m_thrd;

public:
    explicit ScopedThread(std::thread thrd);
    ~ScopedThread();
    ScopedThread(ScopedThread const &) = delete;
    ScopedThread& operator=(ScopedThread const &) = delete;
};
