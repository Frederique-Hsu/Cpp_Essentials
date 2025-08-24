/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <iostream>


int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}

TEST_CASE("Unit Test for Template-Meta-Programming", "[check-cpp-standard]")
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    CHECK(__cplusplus == 202002L);
}