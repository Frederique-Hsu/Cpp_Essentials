/*!
 *  \file       test_my_type_traits.hh
 *  \brief      
 *  
 */


#pragma once


template<class T> constexpr T same(T i)
{
    static_assert(my::is_integral<T>::value, "Integral required");
    return i;
}

template<typename>
struct PM_traits
{
};

template<typename T, typename U>
struct PM_traits<U T::*>
{
    using member_type = U;
};

template<typename T>
void test(T&& x)
{
    std::cout << std::boolalpha;
    
    CHECK(my::is_same_v<T&&, decltype(x)> == true);
    std::cout << "T \t" << my::is_rvalue_reference<T>::value << std::endl
              << "T&& \t" << my::is_rvalue_reference<T&&>::value << std::endl
    << "decltype(x) \t" << my::is_rvalue_reference<decltype(x)>::value << std::endl;
}

class E
{
public:
    template<typename T> E(T&&)
    {
    }
};

template<typename F, typename Class>
void ptr_to_member_func_cvref_test(F Class::*)
{
    using FF = my::add_pointer<F>::type;
    CHECK(my::is_same<F, FF>::value == true);
}

template<typename T, typename U>
constexpr bool is_decay_equal = my::is_same<typename my::decay<T>::type, U>::value;

template<typename A>
void info(const A&)
{
    using Type = typename my::remove_all_extents<A>::type;
    std::cout << "underlying type: " << typeid(Type).name() << std::endl;
}
