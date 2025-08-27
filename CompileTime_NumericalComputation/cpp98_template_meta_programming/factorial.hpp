/*!
 *  \file       factorial.hpp
 *  \brief
 *
 */


#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

    struct A
    {
        int v;      // for sum of n!
        int t;      // for n!
    };

    A factorial(int n);
    void print_factorial();

    int static_factorial(int n);
    void print_static_factorial();

#endif  /* FACTORIAL_HPP */
