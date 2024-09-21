/*!
 *  \file       Concepts.cpp
 *  \brief      
 *  
 */


#include "Concepts.hpp"

#include <utility>
#include <type_traits>
#include <concepts>

template<typename T> bool Copy_Equality(T x)
{
    return T{x} == x;   // 副本应该与元对象相等
}

template<typename T> bool Copy_Assign_Equality(T x, T& y)
{
    return (y = x, y == x);     // 赋值结果应该与元对象相等
}

template<typename T> bool Move_Effect(T x, T& y)
{
    // 移动操作生成的值与移动原应该相等，且移动源可以销毁。
    return (x == y ? T{std::move(x)} == y : true) && can_destroy(y);
}

template<typename T> bool Move_Assign_Effect(T x, T& y, T& z)
{
    return (y == z ? (x = std::move(y), x == z) : true) && can_destroy(y);
}

/*================================================================================================*/

template<typename T, typename U> constexpr bool Common()
{
    return std::is_same_v<T, U>;
}

template<typename T> constexpr bool Totally_Ordered()
{
    return Equality_Comparable<T, T>()
        && Has_Less<T, T>() && Boolean<Less_Result<T, T>>()
        && Has_Greater<T, T>() && Boolean<Greater_Result<T, T>>()
        && Has_Less_Equal<T, T>() && Boolean<Less_Equal_Result<T, T>>()
        && Has_Greater_Equal<T, T>() && Boolean<Greater_Equal_Result<T, T>>();
}

template<typename T> constexpr bool SemiRegular()
{
    return     std::is_destructible<T>()
            && std::is_default_constructible<T>()
            && std::is_move_constructible<T>()
            && std::is_move_assignable<T>()
            && std::is_copy_constructible<T>()
            && std::is_copy_assignable<T>();
}

template<typename T> constexpr bool Regular()
{
    return SemiRegular<T>() && Equality_Comparable<T>();
}

template<typename T> constexpr bool Ordered()
{
    return Regular<T>() && Totally_Ordered<T>();
}

template<typename T, typename U> struct Common_Type
{
    using type = decltype(true? T{} : U{});
};

template<typename T, typename U> constexpr bool Has_Equal()
{
    return std::is_same_v<decltype(std::declval<T>() == std::declval<U>()), bool>;
}

template<typename T, typename U> struct Equal_Result
{
    using type = decltype(std::declval<T>() == std::declval<U>());
};

template<typename T, typename U> constexpr bool Has_Not_Equal()
{
    return std::is_same_v<decltype(std::declval<T>() != std::declval<U>()), bool>;
}

template<typename T, typename U> struct Not_Equal_Result
{
    using type = decltype(std::declval<T>() != std::declval<U>());
};

template<typename T, typename U> constexpr bool Has_Less()
{
    return std::is_same_v<decltype(std::declval<T>() < std::declval<U>()), bool>;
}

template<typename T, typename U> struct Less_Result
{
    using type = decltype(std::declval<T>() < std::declval<U>());
};

template<typename T> constexpr bool Boolean()
{
    return std::is_same_v<bool, std::remove_cvref_t<T>>;
}

template<typename T, typename U> constexpr bool Has_Greater()
{
    return std::is_same_v<decltype(std::declval<T>() > std::declval<U>()), bool>;
}

template<typename T, typename U> struct Greater_Result
{
    using type = decltype(std::declval<T>() > std::declval<U>());
};

template<typename T, typename U> constexpr bool Has_Less_Equal()
{
    return std::is_same_v<decltype(std::declval<T>() <= std::declval<U>()), bool>;
}

template<typename T, typename U> struct Less_Equal_Result
{
    using type = decltype(std::declval<T>() <= std::declval<U>());
};

template<typename T, typename U> constexpr bool Has_Greater_Equal()
{
    return std::is_same_v<decltype(std::declval<T>() >= std::declval<U>()), bool>;
}

template<typename T, typename U> struct Greater_Equal_Result
{
    using type = decltype(std::declval<T>() >= std::declval<U>());
};

template<typename T, typename U> 
constexpr bool Equality_Comparable()
{
    return Common<T, U>()
        && Totally_Ordered<T>()
        && Totally_Ordered<Common_Type<T, U>>()
        && Has_Less<T, U>() && Boolean<Less_Result<T, U>>()
        && Has_Less<U, T>() && Boolean<Less_Result<U, T>>()
        && Has_Greater<T, U>() && Boolean<Greater_Result<T, U>>()
        && Has_Greater<U, T>() && Boolean<Greater_Result<U, T>>()
        && Has_Less_Equal<T, U>() && Boolean<Less_Equal_Result<T, U>>()
        && Has_Less_Equal<U, T>() && Boolean<Less_Equal_Result<U, T>>()
        && Has_Greater_Equal<T, U>() && Boolean<Greater_Equal_Result<T, U>>()
        && Has_Greater_Equal<U, U>() && Boolean<Greater_Equal_Result<U, T>>();
}

template<typename Iter, typename Val>
Iter my::find(Iter begin, Iter end, Val elem)
{
    static_assert(Equality_Comparable<typename Iter::value_type, Val>(), 
                  "find()'s iterator and value arguments must match.");
    
    while (begin != end)
    {
        if (*begin == elem)
        {
            return begin;
        }
        begin++;
    }
    return end;
}

template<int N> constexpr bool Small_Size()
{
    return N <= 8;
}

template<typename T, int N> constexpr bool Stackable()
{
    return Regular<T>() && sizeof(T) * N <= stack_limit;
}

template<typename T, int N>
Buffer<T, N>::Buffer()
{
    for (auto index = 0; index < N; ++index)
    {
        m_buffer[index] = T{};
    }
}

template<typename T, int N> void fct_check()
{
    static_assert(Stackable<T, N>(), "fct_check() buffer will not fit on stack");
    Buffer<T, N> buf;
    // ...
    
}