/*!
 *  \file   functions.hpp
 *  \brief  Declare the function prototypes here
 *
 */


#pragma once

#include <string>

void swap(int*, int*);

#if defined(FUNCTION_REDEFINITION)
/*!
 *  \warning    The below 2 f() functions are duplicated.
 *              they are the same type void(int)
 */
void f(int);            // type is void(int)
void f(const int);      // type is void(int)
#endif

int& max(int& a, int& b, int& c);

/*! \note   the following two declarations are equivalent. */
std::string to_string(int a);           // prefix return type
auto to_string(int a) -> std::string;   // suffix return type

inline int fac(int n)
{
    /*!
     *  \note   It cannot make possible to guarantee that every call of an \a inline function \n
     *          is actually inlined.
     *
     *  \warning    If you want a guarantee that a value is computed at compile time, declare it
     *              \a constexpr and make sure that all functions used in its evaluation are \a constexpr.
     */
    return (n < 2) ? 1 : n * fac(n-1);
}
int fac2(int n);
