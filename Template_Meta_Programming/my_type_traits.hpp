/*!
 *  \file       my_type_traits.hpp
 *  \brief      Learn to define my type_traits for the purpose of template meta programming
 *  
 */


#pragma once

#if defined (__cpp_lib_stdfloat)
    #include <stdfloat>
#else
    #include <cstdint>
#endif

namespace my
{
    template<class T, T v> struct integral_constant
    {
        static constexpr T value = v;
        
        using value_type = T;
        using type = integral_constant<T, v>;
        
        constexpr operator value_type() const noexcept
        {
            return value;
        }
        
        constexpr value_type operator()() const noexcept
        {
            return value;
        }
    };
    
    /*============================================================================================*/
    
    using true_type  = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;
    
    /*============================================================================================*/
    
    template<typename T, typename U> struct is_same : false_type
    {
    };
    
    template<typename T> struct is_same<T, T> : true_type
    {
    };
    
    /*!
     *  \brief      变量模板 (variable template)
     */
    template<typename T, typename U> constexpr bool is_same_v = is_same<T, U>::value;
    
    /*============================================================================================*/
    
    template<typename T> struct remove_cv
    {
        using type = T;
    };
    
    template<typename T> struct remove_cv<const T>
    {
        using type = T;
    };
    
    template<typename T> struct remove_cv<volatile T>
    {
        using type = T;
    };
    
    template<typename T> struct remove_cv<const volatile T>
    {
        using type = T;
    };
    
    template<typename T> struct add_cv
    {
        using type = const volatile T;
    };
    
    /*============================================================================================*/
    
    template<typename T> struct remove_const
    {
        using type = T;
    };
    
    template<typename T> struct remove_const<const T>
    {
        using type = T;
    };
    
    template<typename T> struct add_const
    {
        using type = const T;
    };
    
    /*============================================================================================*/
    
    template<typename T> struct remove_volatile
    {
        using type = T;
    };
    
    template<typename T> struct remove_volatile<volatile T>
    {
        using type = T;
    };
    
    template<typename T> struct add_volatile
    {
        using type = volatile T;
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_void : is_same<void, typename remove_cv<T>::type>
    {
    };
    
    template<typename T> inline constexpr bool is_void_v = is_void<T>::value;
    
    template<typename T> using void_t = void;
    
    /*============================================================================================*/
    
    template<bool B> using bool_constant = integral_constant<bool, B>;
    
    /*!
     *  \note   This implementation uses C++20 facilities
     */
    template<typename T>
    struct is_integral : bool_constant<requires(T t, T *p, void (*fn)(T))   // T* parameter excludes reference types
                                       {
                                           reinterpret_cast<T>(t);     // Exclude class types
                                           fn(0);                      // Exclude enumeration types
                                           p + t;                      // Exclude everything, not yet excluded but integral types
                                       }>
    {
    };
    
    template<typename T> constexpr bool is_integral_v = is_integral<T>::value;
    
    /*============================================================================================*/
    
    template<typename T>
    struct is_floating_point : integral_constant<bool,
                                                 is_same<float, typename remove_cv<T>::type>::value ||
                                                 is_same<double, typename remove_cv<T>::type>::value ||
                                                 is_same<long double, typename remove_cv<T>::type>::value
                                                 #if defined (__cpp_lib_stdflat)
                                                     /*!
                                                      * \attention  C++23 has defined fixed width floating-point types, but currently no compiler had
                                                      *             already accomplished this advanced feature by now.
                                                      */
                                                     is_same<std::float16_t, typename remove_cv<T>::type>::value ||
                                                     is_same<std::float32_t, typename remove_cv<T>::type>::value ||
                                                     is_same<std::float64_t, typename remove_cv<T>::type>::value ||
                                                     is_same<std::float128_t, typename remove_cv<T>::type>::value ||
                                                     is_same<std::bfloat16_t, typename remove_cv<T>::type>::value
                                                 #endif
                                                >
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_array : false_type
    {
    };
    
    template<typename T> struct is_array<T[]> : true_type
    {
    };
    
    template<typename T, std::size_t N> struct is_array<T[N]> : true_type
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_pointer : false_type
    {
    };
    
    template<typename T> struct is_pointer<T*> : true_type
    {
    };
    
    template<typename T> struct is_pointer<T* const> : true_type
    {
    };
    
    template<typename T> struct is_pointer<T* volatile> : true_type
    {
    };
    
    template<typename T> struct is_pointer<T* const volatile> : true_type
    {
    };
    
    template<typename T> constexpr bool is_pointer_v = is_pointer<T>::value;
    
    /*============================================================================================*/
    
    /*!
     *  \note   __is_union(T) 并不是C++表达式，而是Clang/GCC/MSVC等编译器提供的内建函数 (intrinsic)，在编译期间就把结果算出来。
     *          为什么不能像 is_class 那样自己写 SFINAE?
     *          联合体与类的语法差异极小（关键字 union vs. class/struct），没有可移植的纯C++技巧能把两者区分开。
     *          因此标准直接把这项工作下沉到编译器。
     */
    template<typename T> struct is_union : integral_constant<bool, __is_union(T)>
    {
    };
    
    template<typename T> constexpr bool is_union_v = is_union<T>::value;
    
    /*============================================================================================*/
    
    namespace details
    {
        template<typename T> integral_constant<bool, !is_union<T>::value> test(int T::*);
        
        template<typename> false_type test(...);
    }
    
    template<typename T> struct is_class : decltype(details::test<T>(nullptr))
    {
    };
    
    template<typename T> constexpr bool is_class_v = is_class<T>::value;
    
    /*============================================================================================*/
    
    // Primary template
    template<typename> struct is_function : false_type
    {
    };
    // Specialization for regular functions
    template<typename Ret, typename... Args> struct is_function<Ret(Args...)> : true_type
    {
    };
    // Specialization for variadic functions such as std::printf()
    template<typename Ret, typename... Args> struct is_function<Ret(Args......)> : true_type
    {
    };
    // Specialization for function types that have cv-qualifiers
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) volatile> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) volatile> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const volatile> : true_type
    {
    };
    // Specialization for function types that have ref-qualifiers
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) volatile &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) volatile &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const volatile &> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) &&> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const &&> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) volatile &&> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile &&> : true_type
    {
    };
#if (__cplusplus >= 201703L)
    // Specialization for noexcept version of all the above
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) volatile noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) volatile noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const volatile noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) & noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const & noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile & noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) & noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const & noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const volatile & noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) && noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const && noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile && noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) && noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const && noexcept> : true_type
    {
    };
    template<typename Ret, typename... Args> struct is_function<Ret(Args......) const volatile && noexcept> : true_type
    {
    };
#endif
    
    /*============================================================================================*/
    
    template<typename T> struct is_const : false_type
    {
    };
    template<typename T> struct is_const<const T> : true_type
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_volatile : false_type
    {
    };
    template<typename T> struct is_volatile<volatile T> : true_type
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_lvalue_reference : false_type
    {
    };
    template<typename T> struct is_lvalue_reference<T&> : true_type
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_rvalue_reference : false_type
    {
    };
    template<typename T> struct is_rvalue_reference<T&&> : true_type
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct remove_reference
    {
        using type = T;
    };
    template<typename T> struct remove_reference<T&>
    {
        using type = T;
    };
    template<typename T> struct remove_reference<T&&>
    {
        using type = T;
    };
    template<typename T> using remove_reference_t = typename remove_reference<T>::type;
    
    /*============================================================================================*/
    
    namespace details
    {
        template<typename T> struct type_identity
        {
            using type = T;
        };
        template<typename T> auto try_add_lvalue_reference(int) -> type_identity<T&>;
        template<typename T> auto try_add_lvalue_reference(...) -> type_identity<T>;
        template<typename T> auto try_add_rvalue_reference(int) -> type_identity<T&&>;
        template<typename T> auto try_add_rvalue_reference(...) -> type_identity<T>;
    }
    template<typename T> struct add_lvalue_reference : decltype(details::try_add_lvalue_reference<T>(0))
    {
    };
    template<typename T> struct add_rvalue_reference : decltype(details::try_add_rvalue_reference<T>(0))
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct remove_pointer
    {
        using type = T;
    };
    template<typename T> struct remove_pointer<T*>
    {
        using type = T;
    };
    template<typename T> struct remove_pointer<T**>
    {
        using type = T;
    };
    template<typename T> struct remove_pointer<T* const>
    {
        using type = T;
    };
    template<typename T> struct remove_pointer<T* volatile>
    {
        using type = T;
    };
    template<typename T> struct remove_pointer<T* const volatile>
    {
        using type = T;
    };
    
    /*============================================================================================*/
    
    namespace details
    {
        template<typename T>
        auto try_add_pointer(int) -> type_identity<typename remove_reference<T>::type*>;
        
        template<typename T>
        auto try_add_pointer(...) -> type_identity<T>;
    }
    template<typename T> struct add_pointer : decltype(details::try_add_pointer<T>(0))
    {
    };
    
    /*============================================================================================*/
    
    /*!
     *  \note   以下的实现中 __is_* 是编译器内建的函数， 这些内建函数在编译前端就能给出结果，标准库代码层无法复现。
     */
    template<typename T, typename... Args>
    struct is_constructible : bool_constant<__is_constructible(T, Args...)>
    {
    };
    
    template<typename T, typename... Args>
    struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, Args...)>
    {
    };
    
    template<typename T, typename... Args>
    struct is_nothrow_constructible : bool_constant<__is_nothrow_constructible(T, Args...)>
    {
    };
    /*!
     *  \remarks    为什么必须依赖编译器内建？
     *  \li         语法/语义检查：
     *              需要判断 \code T obj(std::declval<Args>()...) \endcode 是否良构 (well-formated)
     *              这涉及重载决议、访问权限、explicit构造函数、初始化规则等，仅靠 SFINAE 无法覆盖全部 corner case (比如聚合初始化，列表初始化、花括号elision).
     *
     *  \li         trivial / noexcept 的额外信息：
     *              判断“构造过程是否平凡”需要知道：
     *              - 构造函数是否 trivial (编译器前端已记录)
     *              - 所有基类 / 非静态成员的构造函数是否 trivial
     *              判断“构造过程是否不抛出异常”需要知道：
     *              - 构造函数及其内部调用的所有函数是否 noexcept (包括析构函数)
     *
     *              综上，这些信息在AST语义分析阶段就已经确定，标准库层面只能拿到结果，无法“算”出来。
     *              标准库只做一层 \code integral_constant \endcode 包装，在源码里找不到“算法”，只能看到一行调用编译器内建函数的代码。
     */
    
    /*============================================================================================*/
    
    template<typename T> struct is_default_constructible : is_constructible<T>
    {
    };
    template<typename T> struct is_trivially_default_constructible : is_trivially_constructible<T>
    {
    };
    template<typename T> struct is_nothrow_default_constructible : is_nothrow_constructible<T>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_copy_constructible
    : is_constructible<T, typename add_lvalue_reference<typename add_const<T>::type>::type>
    {
    };
    template<typename T> struct is_trivially_copy_constructible
        : is_trivially_constructible<T, typename add_lvalue_reference<typename add_const<T>::type>::type>
    {
    };
    template<typename T> struct is_nothrow_copy_constructible
        : is_nothrow_constructible<T, typename add_lvalue_reference<typename add_const<T>::type>::type>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_move_constructible
        : is_constructible<T, typename add_rvalue_reference<T>::type>
    {
    };
    template<typename T> struct is_trivially_move_constructible
        : is_trivially_constructible<T, typename add_rvalue_reference<T>::type>
    {
    };
    template<typename T> struct is_nothrow_move_constructible
        : is_nothrow_constructible<T, typename add_rvalue_reference<T>::type>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T, typename U>
    struct is_assignable : bool_constant<__is_assignable(T, U)>
    {
    };
    template<typename T, typename U>
    struct is_trivially_assignable : bool_constant<__is_trivially_assignable(T, U)>
    {
    };
    template<typename T, typename U>
    struct is_nothrow_assignable : bool_constant<__is_nothrow_assignable(T, U)>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_copy_assignable : is_assignable<typename add_lvalue_reference<T>::type,
                                                                   typename add_lvalue_reference<const T>::type>
    {
    };
    template<typename T>
    struct is_trivially_copy_assignable : is_trivially_assignable<typename add_lvalue_reference<T>::type,
                                                                  typename add_lvalue_reference<const T>::type>
    {
    };
    template<typename T>
    struct is_nothrow_copy_assignable : is_nothrow_assignable<typename add_lvalue_reference<T>::type,
                                                              typename add_lvalue_reference<const T>::type>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T>
    struct is_move_assignable : is_assignable<typename add_lvalue_reference<T>::type,
                                              typename add_rvalue_reference<T>::type>
    {
    };
    template<typename T>
    struct is_trivially_move_assignable : is_trivially_assignable<typename add_lvalue_reference<T>::type,
                                                                  typename add_rvalue_reference<T>::type>
    {
    };
    template<typename T>
    struct is_nothrow_move_assignable : is_nothrow_assignable<typename add_lvalue_reference<T>::type,
                                                              typename add_rvalue_reference<T>::type>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct is_destructible : integral_constant<bool,
                                                                    requires(T obj)
                                                                    {
                                                                        obj.~T();
                                                                    }>
    {
    };
    template<typename T> struct is_nothrow_destructible : integral_constant<bool,
                                                                            requires(T obj)
                                                                            {
                                                                                { obj.~T() } noexcept;
                                                                            }>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T> struct has_virtual_destructor : bool_constant<__has_virtual_destructor(T)>
    {
    };
    
    /*============================================================================================*/
    
    namespace details
    {
        template<typename B> true_type  test_ptr_conv(const volatile B*);
        template<typename>   false_type test_ptr_conv(const volatile void*);
        
        template<typename Base, typename Derived>
        auto test_is_base_of(int) -> decltype(test_ptr_conv<Base>(static_cast<Derived *>(nullptr)));
        
        template<typename Base, typename Derived>
        auto test_is_base_of(...) -> true_type;
    }
    
    template<typename Base, typename Derived>
    struct is_base_of : integral_constant<bool,
                                          is_class<Base>::value &&
                                          is_class<Derived>::value &&
                                          decltype(details::test_is_base_of<Base, Derived>(0))::value>
    {
    };
    
    /*============================================================================================*/
    
    template<typename T>
    typename add_rvalue_reference<T>::type declval() noexcept
    {
        static_assert(false, "declval not allowed in an evaluated context");
    }
    
    namespace details
    {
        template<typename T>
        auto test_returnable(int) -> decltype(void(static_cast<T(*)()>(nullptr)), true_type{});
        
        template<typename T>
        auto test_returnable(...) -> false_type;
        
        template<typename From, typename To>
        auto test_implicitly_convertible(int) -> decltype(void(declval<void(&)(To)>()(declval<From>())), true_type{});
        
        template<typename From, typename To>
        auto test_implicitly_convertible(...) -> false_type;
    }
    
    template<typename From, typename To>
    struct is_convertible : integral_constant<
        bool,
        (decltype(details::test_returnable<To>(0))::value &&
         decltype(details::test_implicitly_convertible<From, To>(0))::value) ||
        (is_void<From>::value && is_void<To>::value)>
    {
    };
    
    /*============================================================================================*/
    
    template<bool B, typename T, typename F> struct conditional
    {
        using type = T;
    };
    template<typename T, typename F> struct conditional<false, T, F>
    {
        using type = F;
    };
    
    /*============================================================================================*/
    
    template<typename T> struct remove_extent
    {
        using type = T;
    };
    template<typename T> struct remove_extent<T[]>
    {
        using type = T;
    };
    template<typename T, std::size_t N> struct remove_extent<T[N]>
    {
        using type = T;
    };
    
    template<typename T> struct remove_all_extents
    {
        using type = T;
    };
    template<typename T> struct remove_all_extents<T[]>
    {
        using type = typename remove_all_extents<T>::type;
    };
    template<typename T, std::size_t N> struct remove_all_extents<T[N]>
    {
        using type = typename remove_all_extents<T>::type;
    };
    
    /*============================================================================================*/
    
    template<typename T> struct decay
    {
    private:
        using U = typename remove_reference<T>::type;
    public:
        using type = typename conditional<is_array<U>::value,
                                          typename add_pointer<typename remove_extent<U>::type>::type,
                                          typename conditional<is_function<U>::value,
                                                               typename add_pointer<U>::type,
                                                               typename remove_cv<U>::type
                                                              >::type
                                         >::type;
    };
    
    template<typename T> using decay_t = typename decay<T>::type;
}
