/*!
 *  \file       HelloWorld.cpp
 *  \brief      Study how to write the first CMake project.
 *  \author     Frederique Hsu  frederique.hsu@outlook.com
 *  \date       Sun.    06 Aug. 2023
 *  
 */


#include <string>
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Hello, welcome to the CMake build system world!" << std::endl;

    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    return 0;
}