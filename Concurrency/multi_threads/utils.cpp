/*!
 *  \file       utils.cpp
 *  \brief
 *
 */


#include "utils.hpp"

#include <iostream>

void print_thread_id(std::thread& thrd)
{
    if (thrd.get_id() == std::thread::id{})
    {
        std::cout << "thread not joinable." << std::endl;
    }
    else
    {
        std::cout << "thread id is " << thrd.get_id() << ".\n" << std::endl;
    }
}
