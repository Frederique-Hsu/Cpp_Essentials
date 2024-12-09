/*!
 *  \file       my_thread.cpp
 *  \brief      
 *  
 */


#include "my_thread.hpp"



MyThread::MyThread(int a, int b) : m_a{a}, m_b{b}, result{0}, 
                                   is_ready{false}, is_done{false}
{
}

void MyThread::run()
{
    is_ready = true;

    while (!is_ready)
    {
    }

    result = m_a + m_b;
    is_done = true;
}

int MyThread::getResult() const
{
    while (!is_done)
    {
        // calculating...
    }
    return result;
}


MyImprovedThread::MyImprovedThread(int a, int b) : m_a{a}, m_b{b}, result{0}
{
}

void MyImprovedThread::run()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    result = m_a + m_b;
    m_cv.notify_one();
}

int MyImprovedThread::getResult()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_cv.wait(lock, [this]() { return result != 0; });
    return result;
}