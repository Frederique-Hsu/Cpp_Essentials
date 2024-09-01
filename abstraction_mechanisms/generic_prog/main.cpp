/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <catch2/catch_session.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    return Catch::Session().run(argc, argv);
}