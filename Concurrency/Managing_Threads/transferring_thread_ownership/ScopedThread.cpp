/*!
 *  \file       ScopedThread.cpp
 *  \brief
 *
 */


#include "ScopedThread.hpp"

#include <stdexcept>


ScopedThread::ScopedThread(std::thread thrd) : m_thrd{std::move(thrd)}
{
    if (!m_thrd.joinable())
    {
        throw std::logic_error("No thread");
    }
}

ScopedThread::~ScopedThread()
{
    m_thrd.join();
}
