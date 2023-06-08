/*!
 *  \file       statements.hpp
 *  \brief
 *
 */


#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

    #include <vector>

    enum E1
    {
        a,
        b
    };

    enum class E2
    {
        a,
        b
    };

    void check(E1 x, E2 y);

    enum class Vessel
    {
        cup,
        glass,
        goblet,
        chalice,
    };

    void problematic(Vessel v);

    int sum(std::vector<int>& vec);
    void increment(std::vector<int>& vec);



#endif  /* STATEMENTS_HPP */
