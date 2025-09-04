/*!
 *  \file       background_task.cpp
 *  \brief
 *
 */


#include "background_task.hpp"

#include <iostream>


void BackgroundTask::operator()() const
{
    doSomething();
    doSomethingElse();
}

void doSomething()
{
    /*!
     *  \todo   implement this function in the future
     */
    std::cout << "Do something here." << std::endl;
}

void doSomethingElse()
{
    /*!
     *  \todo   implement this function in the future
     */
    std::cout << "Do something else here." << std::endl;
}
