/*!
 *  \file       main.cpp
 *  \brief
 *
 */



#include <iostream>

#include "transferring_threads.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    
    transferThreadOwnership();
    spawnThreadsAndWaitCompletion();

    return 0;
}
