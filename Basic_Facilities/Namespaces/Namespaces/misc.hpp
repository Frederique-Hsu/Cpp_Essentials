/*!
 *  \file       misc.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

namespace Parser
{
double expr(bool);
double term(bool);
double prim(bool);
}

namespace N
{
void f(int);
void f(std::string);
}

void g();
