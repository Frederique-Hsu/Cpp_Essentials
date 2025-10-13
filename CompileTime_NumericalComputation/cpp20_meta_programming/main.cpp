/*!
 *  \file       main.cpp
 *  \brief      研究 C++20 的元编程 
 *  \details    C++20 在元编程中有很好的改进，将 constexpr 代之以 consteval，便可以在编译期发现无法进行
 *              编译期计算的元编程错误。
 */


#include <iostream>

#include "consteval_meta.hpp"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;
    static_assert(__cplusplus == 202002L, "The C++ standard no. you selected is incorrect.");
    
    access_consteval_object();

    return 0;
}
