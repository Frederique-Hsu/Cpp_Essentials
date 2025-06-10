/*!
 *  \file       my_threads.hpp
 *  \brief      
 *  
 */


#pragma once


#include <atomic>
#include <mutex>
#include <condition_variable>

class MyThread
{
public:
    MyThread(int a, int b);
private:
    int m_a;
    int m_b;
    int result;
public:
    std::atomic<bool> is_ready;
    std::atomic<bool> is_done;
public:
    void run();
    int getResult() const;
};

class MyImprovedThread
{
public:
    MyImprovedThread(int a, int b);
private:
    int m_a;
    int m_b;
    int result;

    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
public:
    void run();
    int getResult();
};