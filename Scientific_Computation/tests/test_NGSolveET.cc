/*!
 *  \file       test_NGSolveET.cc
 *  \brief      
 *  
 */


#include "../NGSolve_Expression_Templates/MyFirstVec.hpp"
#include "../NGSolve_Expression_Templates/MyFirstVec.cpp"

#include <gtest/gtest.h>
#include <chrono>
#include <iostream>

TEST(UTest4NGSolveET, CheckMyFirstVecClassTemplate)
{
    // std::chrono::time_point<std::chrono::system_clock> start, end;
    
    int Num = 10;

    auto start = std::chrono::high_resolution_clock::now();
    MyFirstVec<double> x(Num), y(Num), z(Num);
    x = 2.0;
    y = 3.0;
    z = 1.1 * (1.1 * (3.0 * x + y) + x) + y;

    std::cout << z << std::endl;
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << "nano-sec\n" << std::endl;
}