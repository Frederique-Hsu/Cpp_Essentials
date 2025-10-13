/*!
 *  \file       functor.cpp
 *  \brief
 *
 */


#include "functor.hpp"

#include <thread>
#include <iostream>

void increment(int& i)
{
    ++i;
}

Functor::Functor(int& i) : imem{i}
{
}

void Functor::operator()()
{
    for (unsigned index = 0; index < 1000000; ++index)
    {
        increment(imem);
    }
}

void doSomethingInCurrentThread()
{
    std::cout << "Do something in current thread." << std::endl;
}

void waitThreadFinished()
{
    int some_local_state = 0;

    Functor my_functor(some_local_state);
    std::thread task(my_functor);

    try
    {
        doSomethingInCurrentThread();
    }
    catch (...)
    {
        task.join();
        throw std::runtime_error("Failed!");
    }
    task.join();
}
