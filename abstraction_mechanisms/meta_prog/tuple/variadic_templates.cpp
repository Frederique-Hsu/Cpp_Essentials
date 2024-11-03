/*!
 *  \file       variadic_templates.cpp
 *  \brief      
 *  
 */


#include "variadic_templates.hpp"

#include <iostream>
#include <stdexcept>
#include <type_traits>

template<typename T> constexpr bool Is_Integral()
{
    return std::is_integral<T>::value;
}

template<typename T> constexpr bool Is_Floating_Point()
{
    return std::is_floating_point<T>::value;
}

template<typename T> constexpr bool Is_String()
{
    return typeid(T) == typeid(char*) || typeid(T) == typeid(char[]);
}

template<typename T> constexpr bool Is_C_Style_String()
{
    return std::__is_char<T>::value;
}

template<typename T, typename... Args>              // 可变参数模板，类型参数列表： 一个或多个类型参数
void printf(const char* s, T value, Args... args)   // 函数参数列表： 两个或多个参数
{
#if true
    while (s && *s)
    {
        if ((*s == '%') and (*++s != '%'))          // 一个个数说明符 （忽略其具体是什么）
        {
            std::cout << value;                     // 使用第一个非格式实参
            return printf(++s, args...);            // 用实参列表尾作为参数进行递归调用
        }
        std::cout << *s++;
    }
#else
    while (s && *s)
    {
        if (*s == '%')
        {
            switch (*++s)
            {
            case '%':
                break;
            case 's':
                if (!Is_C_Style_String<T>() && !Is_String<T>())
                {
                    throw std::runtime_error("Bad printf() format.");
                }
                break;
            case 'd':
                if (!Is_Integral<T>())
                {
                    throw std::runtime_error("Bad printf() format");
                }
                break;
            case 'g':
                if (!Is_Floating_Point<T>())
                {
                    throw std::runtime_error("Bad printf() format");
                }
                break;
            }
            std::cout << value;
            return printf(++s, args...);
        }
        std::cout << *s++;
    }
#endif
    throw std::runtime_error("extra arguments provided to printf");
}


/*================================================================================================*/

namespace my
{
    template<typename Head, typename... Tail>
    constexpr tuple<Head, Tail...>::tuple()
    {
    }

    template<typename Head, typename... Tail>
    tuple<Head, Tail...>::tuple(const Head& vhead, const Tail&... vtail) : inherited(vtail...), m_head{vhead}
    {
    }

    template<typename Head, typename... Tail> template<typename... ValueTypes>
    tuple<Head, Tail...>::tuple(const tuple<ValueTypes...>& other) : inherited(other.tail()), m_head{other.head()}
    {
    }

    template<typename Head, typename... Tail> template<typename... ValueTypes>
    tuple<Head, Tail...>& tuple<Head, Tail...>::operator=(const tuple<ValueTypes...>& other)
    {
        m_head = other.head();
        tail() = other.tail();
        return *this;
    }

    template<typename Head, typename... Tail>
    Head& tuple<Head, Tail...>::head()
    {
        return m_head;
    }

    template<typename Head, typename... Tail>
    const Head& tuple<Head, Tail...>::head() const
    {
        return m_head;
    }

    template<typename Head, typename... Tail>
    typename tuple<Head, Tail...>::inherited& tuple<Head, Tail...>::tail()
    {
        return *this;
    }

    template<typename Head, typename... Tail>
    const typename tuple<Head, Tail...>::inherited& tuple<Head, Tail...>::tail() const
    {
        return *this;
    }

    template<typename Head, typename... Tail>
    Head head(tuple<Head, Tail...>& tpl)
    {
        return std::get<0>(tpl);
    }

    template<typename Head, typename... Tail>
    tuple<Tail&...> tail(tuple<Head, Tail...>& tpl)
    {
        return tuple<Tail&...>(tpl);
    }
}