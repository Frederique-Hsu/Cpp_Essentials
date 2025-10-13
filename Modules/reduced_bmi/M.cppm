/*!
 *  \file       M.cppm
 *  \brief      
 *  
 */


module;

#include "foo.h"

export module M;

template<typename T> int use_f()
{
    N::X x;
    return f(x, 123);
}

template<typename T> int use_g()
{
    N::X x;
    return N::g((T(), x));
}

template<typename T> int use_h()
{
    N::X x;
    return N::h((T(), x));
}

int k = use_h<int>();