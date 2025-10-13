/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <iostream>
#include <thread>

#include "functor.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    int some_local_state = 0;
    Functor my_functor(some_local_state);
    std::thread my_thread(my_functor);
    std::this_thread::sleep_for(std::chrono::microseconds(50));

    /*!
     *  \warning    不等待线程结束，新线程可能还在运行。
     */
    my_thread.detach();

    std::cout << "Now the some_local_state = " << some_local_state << std::endl;

    return EXIT_SUCCESS;
}
