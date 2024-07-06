/*!
 *  \file       misc.cpp
 *  \brief
 *
 */


#include "misc.hpp"

#include <iostream>

double Parser::expr(bool)
{
    return double{};
}

double Parser::term(bool)
{
    return double{};
}

double Parser::prim(bool)
{
    return double{};
}


namespace N
{
void f(int num)
{
    std::cout << "called N::f(int{" << num << "})" << std::endl;
}

void f(std::string str)
{
    std::cout << "called N::f(string{\"" << str << "\"})" << std::endl;
}
}

void g()
{
    using N::f;     /*! \remark 当用于一个重载的名字时，using声明会应用于其所有重载版本。 */

    f(789);
    f("Bruce Lee");
}
