/*!
 *  \file       main.cpp
 *  \brief      This file just implements the main() portal function for cuurent project.
 * 
 */


#include <catch2/catch_session.hpp>


int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}