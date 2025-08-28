/*!
 *  \file       hello_concurrency_world.cpp
 *  \brief      
 *  
 */


#include <iostream>
#include <thread>


void hello()
{
    std::cout << "Hello, Concurrency World!" << std::endl;
}


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::thread t(hello);
    t.join();
}