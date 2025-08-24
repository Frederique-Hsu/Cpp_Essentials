/*!
 *  \file       test_my_enable_if.hh
 *  \brief      
 *  
 */


#pragma once

#include "my_type_traits.hpp"

#include <type_traits>

struct T
{
    enum 
    { 
        int_t,
        float_t
    } type;

    template<typename Integer, 
             my::enable_if_t<my::is_integral<Integer>::value, bool> = true>
    T(Integer) : type{int_t}
    {
    }

    template<typename Floating, 
             my::enable_if_t<my::is_floating_point<Floating>::value, bool> = true>
    T(Floating) : type{float_t}
    {
    }
};

#if false
    namespace first
    {
        struct X
        {
            enum
            {
                value1 = true,
                value2 = true
            };
        };

        template<typename T, my::enable_if_t<T::value1, int> = 0> void func()
        {
            std::cout << "first::func<T, int = 0>()" << std::endl;
        }

        template<> void func<X>()
        {
            std::cout << "Specialized first::func<X>()" << std::endl;
        }
    }

    namespace second
    {
        struct X
        {
            enum
            {
                value1 = true,
                value2 = true
            };
        };

        template<typename T, my::enable_if_t<T::value2, int> = 0> void func()
        {
            std::cout << "second::func<T, int = 0>()" << std::endl;
        }

        template<> void func<X>()
        {
            std::cout << "Specialized second::func<X>()" << std::endl;
        }
    }
#endif

namespace detail
{
    void* voidify(const volatile void* ptr) noexcept
    {
        return const_cast<void*>(ptr);
    }
}

template<typename T>
typename my::enable_if<std::is_trivially_default_constructible<T>::value>::type construct(T*)
{
    std::cout << "default constructing trivially default constructible T" << std::endl;
}

template<typename T>
typename my::enable_if<!std::is_trivially_default_constructible<T>::value>::type construct(T* p)
{
    std::cout << "default constructing non-trivially default constructible T" << std::endl;
    ::new(detail::voidify(p)) T;
}

template<typename T, typename... Args>
my::enable_if_t<std::is_constructible<T, Args&&...>::value> construct(T* p, Args&&... args)
{
    std::cout << "constructing T with operation" << std::endl;
    ::new(detail::voidify(p)) T(static_cast<Args&&>(args)...);
}

template<typename T,
         typename my::enable_if<!(std::is_trivially_destructible<T>{}) && (std::is_class<T>{} || std::is_union<T>{}),
                                bool>::type = true
        >
void destroy(T* t)
{
    std::cout << "destroying non-trivially destructible T" << std::endl;
    t->~T();
}

template<typename T,
         typename = my::enable_if_t<my::is_array<T>::value>
        >
void destroy(T* t)
{
    for (unsigned index = 0; index < std::extent<T>::value; ++index)
    {
        destroy((*t)[index]);
    }
}


template<typename T, typename Enabled = void>
class Test
{
};

template<typename T>
class Test<T, typename my::enable_if<my::is_floating_point<T>::value>::type>
{
};
