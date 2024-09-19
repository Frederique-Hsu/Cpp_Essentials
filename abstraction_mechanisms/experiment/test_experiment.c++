/*!
 *  \file       test_experiment.c++
 *  \brief      
 *  
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>

/*!
 *  \remark     做一个小实验
 *              
 *  \details    从C++14开始，可以支持在Lamba表达式中利用模板来增强灵活性和功能，使得Lambda可以处理
 *              更广泛的类型参数。
 *              以下是实验代码：
 */


TEST_CASE("Make a small experiment to verify the C++ feature, that is: utilize the template in a Lambda expression.", "[Lambda][Template]")
{
    auto fn = []<typename T>(T t1, T t2) -> T
    {
        return t1 + t2;
    };
    
    SECTION("How to define the lambda expression with template, and verify it?")
    {
        auto result = fn(2, 6);
        std::cout << "The result = " << result << std::endl;
        
        CHECK(result == 8);
    }
}