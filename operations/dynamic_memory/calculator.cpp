/*!
 *  \file       calculator.cpp
 *  \brief
 *
 */


#include "calculator.hpp"

#include <iostream>

static TokenStream ts{std::cin};

Enode* expr(bool get)
{
    Enode* left = term(get);

    while (true)
    {
        switch (ts.current().kind)
        {
        case Kind::plus:
        case Kind::minus:
            left = new Enode{ts.current().kind, left, term(true)};
            break;
        default:
            return left;
        }
    }
    return left;
}

Enode* term(bool get)
{
    return new Enode;
}
