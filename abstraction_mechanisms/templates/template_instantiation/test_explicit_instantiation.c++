/*!
 *  \file       test_explicit_instantiation.c++
 *  \brief      
 *  
 */


#include <cmath>

#include <iostream>
#include <iomanip>
#include <ios>

#include "MyVector.hpp"
#include "explicit_instantiation.hpp"

#include <gtest/gtest.h>

/*!
 *  \attention  在此编译单元实例化，使用此实例化点
 */
template class MyVector<int>;    

[[maybe_unused]] static void calculate(MyVector<int>& ivec,
                                       double (*calculator)(int))
{
    for (auto index = 0; index < ivec.size(); ++index)
    {
        double result = calculator(ivec[index]);
        
        std::cout << std::setw(10) << std::right << std::setprecision(6) 
                  << result << "    ";
        if ((index+1) % 5 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

TEST(UTest4ExplicitTemplateInstantiation, CheckHowToForbidImplicitInstantiation)
{
    auto cosine = [](int num)
    {
        return std::cos(num);
    };
    
    MyVector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    calculate(numbers, cosine);
}

TEST(UTest4ExplicitTemplateInstantiation, CheckFunctionTemplateSpecialization)
{
    double pi = 3.1415826;
    int converted_pi = convert<int>(pi);
    EXPECT_EQ(converted_pi, 3);
}