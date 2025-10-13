/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <iostream>

#include "passing_arguments.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    passPointerToThreadFunction(50);
    passReferenceToThreadFunction(125);
    passObjectMethodToThreadFunction();

    return EXIT_SUCCESS;
}
