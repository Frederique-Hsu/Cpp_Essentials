/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <iostream>

#include "recursive_meta_programming.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    static_assert(__cplusplus == 201103L, "The C++ standard no. is incorrect.");

    print_factorial_sum();

    return 0;
}
