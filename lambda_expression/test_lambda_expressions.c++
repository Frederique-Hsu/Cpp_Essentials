/*!
 *  \file       test_lambda_expressions.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <cmath>

#include "lambda_expressions.hpp"
#include "lambda.hpp"

TEST(UTester4LambdaExpressions, CheckHowLambdaExprWorks)
{
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 17, 19, 20};

    std::cout << "These numbers will be print out as following: " << std::endl;
    print_modulo(nums, std::cout, 3);

    std::cout << "The same numbers are: " << std::endl;
    Modulo_print mod(std::cout, 3);
    for (auto& elem : nums)
    {
        mod(elem);
    }
}

TEST(UTester4LambdaExpressions, CheckHowLambdaExpressionMutable)
{
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    calculate_algo(numbers);

    cout << "Current numbers' size become " << numbers.size() << endl;
}

void check_lambda_return_type(double y)
{
    auto z = [&](){ std::sqrt(y); };
    z();

    auto z1 = [=](int x){ return x + y; };
    std::cout << "z1(5) = " << z1(5) << std::endl;

    auto z2 = [=, &y](){
        if (y)
            return 1;
        else
            return 2;
    };
    std::cout << "z2() = " << z2() << std::endl;

    auto z3 = [=, &y]() -> int {
        if (y)
            return 1;
        else
            return 2;
    };
    std::cout << "z3() = " << z3() << std::endl;
}

TEST(UTester4LambdaExpressions, CheckLambdaExpressionReturnType)
{
    check_lambda_return_type(0.25);
}

TEST(UTester4LambdaExpressions, CheckLambdaType)
{
    std::function<void(char* b, char* e)> rev = [&](char* b, char* e)
                                                {
                                                    if (1 < e - b)
                                                    {
                                                        std::swap(*b, *--e);
                                                        rev(++b, e);
                                                    }
                                                };
    std::string s1("hello"), s2("world");
    rev(&s1[0], &s1[0] + s1.size());
    rev(&s2[0], &s2[0] + s2.size());

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;

    std::string str1("lambda"), str2("expression");
    reverse_string(str1, str2);
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    /*!
     *  \warning    如果一个lambda什么也不捕获，则可以将其赋值给一个指向正确类型函数的指针。
     */
    double (*p1)(double) = [](double a){ return std::sqrt(a); };
    // double (*p2)(double) = [&](double a){ return std::sqrt(a); };   // 错误：lambda捕获了内容
    // double (*p3)(int) = [](double a){ return std::sqrt(a); };      // 错误： 参数类型不匹配

    std::cout << "p1(9) = " << p1(9) << std::endl;
}
