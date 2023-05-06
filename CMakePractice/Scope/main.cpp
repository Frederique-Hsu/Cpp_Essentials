/*!
 *  \file       main.cpp
 *  \brief      This file implements the main() portal function for current project,
 *  
 */



#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard number is: " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    return 0;
}