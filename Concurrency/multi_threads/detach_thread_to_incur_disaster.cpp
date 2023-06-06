/*!
 *  \file       detach_thread_to_incur_disaster.cpp
 *  \brief      Demo how the disaster happens when detaching a thread from the main process.
 *  
 */


#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
    int var = 0;

    std::thread disaster([&](){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        ++var;
        std::cout << "Now current var = " << var << std::endl;
    });
    disaster.detach();

    std::cout << "Current var in the main thread is " << var << std::endl;

    return 0;
}