/*!
 *  \file       select.hpp
 *  \brief      
 *  
 */


#pragma once

#include <type_traits>
#include <tuple>

namespace my
{
    template<bool Cond, typename TrueType, typename FalseType>
    struct conditional
    {
        using type = TrueType;
    };

    template<typename TrueType, typename FalseType>
    struct conditional<false, TrueType, FalseType>
    {
        using type = FalseType;
    };

    template<bool Cond, typename T, typename F>
    using Conditional = typename std::conditional<Cond, T, F>::type;
}

struct Square
{
    constexpr int operator()(int side)
    {
        return side * side;
    }
};

struct Cube
{
    constexpr int operator()(int side)
    {
        return side * side * side;
    }
};


namespace my
{
    class Nil
    {
    };

    template<int i, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil> struct select;

    template<int i, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
    using Select = typename select<i, T1, T2, T3, T4>::type;

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<0, T1, T2, T3, T4>
    {
        using type = T1;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<1, T1, T2, T3, T4>
    {
        using type = T2;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<2, T1, T2, T3, T4>
    {
        using type = T3;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<3, T1, T2, T3, T4>
    {
        using type = T4;
    };
}

namespace estd
{
/*================================================================================================*/

    template<unsigned i, typename... Cases> struct select;     // 一般情况: 不会被实例化

    template<unsigned i, typename T, typename... Cases>
    struct select<i, T, Cases...> : select<i-1, Cases...>     // 逐个缩减
    {
    };

    template<typename T, typename... Cases>
    struct select<0, T, Cases...>      // 最终情况： i = 0
    {
        using type = T;
    };

    template<unsigned i, typename... Cases>
    using Select = typename select<i, Cases...>::type;

/*================================================================================================*/
}