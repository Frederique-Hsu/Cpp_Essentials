/*!
 *  \file       main.cpp
 *  \brief      
 *  
 */


#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}


TEST_CASE("Check the C++ profile information", "[C++ standard]")
{
    INFO("Current C++ standard no. is " + std::to_string(__cplusplus));
    INFO("Current program is " + std::to_string(sizeof(void*) * 8) + "-bits.");
    CHECK(true);
}