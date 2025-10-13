/*!
 *  \file       JoiningThread.cpp
 *  \brief
 *
 */


#include "JoiningThread.hpp"


JoiningThread::JoiningThread(std::thread thrd) noexcept : m_thrd(std::move(thrd))
{
}

JoiningThread::JoiningThread(JoiningThread&& other) noexcept : m_thrd(std::move(other.m_thrd))
{
}

JoiningThread& JoiningThread::operator=(JoiningThread&& other) noexcept
{
    if (joinable())
    {
        join();
    }
    m_thrd = std::move(other.m_thrd);
    return *this;
}

JoiningThread& JoiningThread::operator=(std::thread other) noexcept
{
    if (joinable())
    {
        join();
    }
    m_thrd = std::move(other);
    return *this;
}

JoiningThread::~JoiningThread() noexcept
{
    if (joinable())
    {
        join();
    }
}

void JoiningThread::swap(JoiningThread& other) noexcept
{
    m_thrd.swap(other.m_thrd);
}

bool JoiningThread::joinable() const noexcept
{
    return m_thrd.joinable();
}

void JoiningThread::join()
{
    m_thrd.join();
}

void JoiningThread::detach()
{
    m_thrd.detach();
}

std::thread::id JoiningThread::get_id() const noexcept
{
    return m_thrd.get_id();
}

std::thread& JoiningThread::as_thread() noexcept
{
    return m_thrd;
}

const std::thread& JoiningThread::as_thread() const noexcept
{
    return m_thrd;
}
