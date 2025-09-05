/*!
 *  \file       main.cpp
 *  \brief      Running the thread in the background.
 *
 */


#include <iostream>
#include <thread>
#include <cassert>

#include "background_work.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    std::thread task(doBackgroundWork);
    task.detach();
    assert(task.joinable() == false);

    editDocument("foo.doc");


    return 0;
}
