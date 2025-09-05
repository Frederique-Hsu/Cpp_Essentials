/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <iostream>

#include "functor.hpp"
#include "thread_guard.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    waitThreadFinished();

    int local_state = 0;
    Functor functor(local_state);
    std::thread task(functor);

    ThreadGuard guard(task);

    auto processMainThread = [&local_state]() -> void
    {
        std::cout << "Wait for 100us from the main thread." << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(100));

        std::cout << "Now the local_state = " << local_state << std::endl;
    };
    processMainThread();

    return 0;
}
