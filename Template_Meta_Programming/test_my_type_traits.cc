/*!
 *  \file       test_my_type_traits.cc
 *  \brief      Validate whether my type_traits works well.
 *  
 */


#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <valarray>
#include <string>
#include <string_view>

#include "my_type_traits.hpp"
#include "test_my_type_traits.hh"


TEST_CASE("Unit Test for my type_traits", "[my_type_traits]")
{
    #define SHOW(...)   std::cout << # __VA_ARGS__ << " : " << __VA_ARGS__ << std::endl
    
    SECTION("Check my::is_same")
    {
        std::cout << std::boolalpha;
        
        CHECK(my::is_same<int, std::int32_t>::value == true);
        CHECK(my::is_same<int, std::int64_t>::value == false);
        
        SHOW(my::is_same_v<int, std::int32_t>);
        SHOW(my::is_same_v<int, std::int64_t>);
        
        long double num1 = 1.0;
        long double num2 = -3.0;
        CHECK(my::is_same<decltype(num1), decltype(num2)>::value == true);
        
        static_assert(my::is_same<float, std::int32_t>::value == false);
        
        // 'int' is implicitly 'unsigned'
        CHECK(my::is_same<int, int>::value == true);
        CHECK(my::is_same<int, unsigned int>::value == false);
        CHECK(my::is_same<int, signed int>::value == true);
        // but const-qualified type T is not same as non-const T
        CHECK(my::is_same<const int, int>::value == false);
        
        // Unlike other types, 'char' is neither 'unsigned' not 'signed'
        CHECK(my::is_same_v<char, char> == true);
        CHECK(my::is_same_v<char, unsigned char> == false);
        CHECK(my::is_same_v<char, signed char> == false);
    }
    
    SECTION("Check my::remove_cv")
    {
        CHECK(my::is_same_v<my::remove_cv<int>::type, int> == true);
        CHECK(my::is_same_v<my::remove_cv<const int>::type, int> == true);
        CHECK(my::is_same_v<my::remove_cv<volatile int>::type, int> == true);
        CHECK(my::is_same_v<my::remove_cv<const volatile int>::type, int> == true);
    }
    
    SECTION("Check my::remove_const")
    {
        CHECK(my::is_same<my::remove_const<double>::type, double>::value == true);
        CHECK(my::is_same<my::remove_const<const double>::type, double>::value == true);
    }
    
    SECTION("Check my::remove_volatile")
    {
        CHECK(my::is_same_v<my::remove_volatile<float>::type, float> == true);
        CHECK(my::is_same_v<my::remove_volatile<volatile float>::type, float> == true);
    }
    
    SECTION("Check my::is_void and my::is_void_v")
    {
        void foo();
        
        CHECK(my::is_void<void>::value == true);
        CHECK(my::is_void<const void>::value == true);
        CHECK(my::is_void_v<volatile void> == true);
        CHECK(my::is_void_v<const volatile void> == true);
        
        CHECK(my::is_void<void*>::value == false);
        CHECK(my::is_void<int>::value == false);
        CHECK(my::is_void<decltype(foo)>::value == false);
        
        CHECK(my::is_void_v<my::is_void<void>> == false);
    }
    
    SECTION("Check my::is_integral")
    {
        CHECK(my::is_integral<float>::value == false);
        CHECK(my::is_integral<int*>::value == false);
        CHECK(my::is_integral<int>::value == true);
        CHECK(my::is_integral_v<const int> == true);
        CHECK(my::is_integral_v<bool> == true);
        CHECK(my::is_integral_v<char> == true);
        
        class A
        {
        };
        CHECK(my::is_integral<A>::value == false);
        
        struct B
        {
            int x : 4;
        };
        CHECK(my::is_integral<B>::value == false);
        
        using BF = decltype(B::x);  // bit-field's type, still an integral type
        CHECK(my::is_integral_v<BF> == true);
        
        enum E : int
        {
        };
        CHECK(my::is_integral<E>::value == false);
        
        CHECK(same('"') == 042);
    }
    
    SECTION("Check my::is_floating_point")
    {
        class A {};
        CHECK(my::is_floating_point<A>::value == false);
        CHECK(my::is_floating_point<float>::value == true);
        CHECK(my::is_floating_point<float&>::value == false);
        CHECK(my::is_floating_point<double>::value == true);
        CHECK(my::is_floating_point<long double>::value == true);
        CHECK(my::is_floating_point<double&>::value == false);
        CHECK(my::is_floating_point<int>::value == false);
    }
    
    SECTION("Check my::is_array")
    {
        class A {};
        CHECK(my::is_array<A>::value == false);
        CHECK(my::is_array<A[]>::value == true);
        CHECK(my::is_array<A[3]>::value == true);
        
        CHECK(my::is_array<float>::value == false);
        CHECK(my::is_array<int>::value == false);
        CHECK(my::is_array<int[]>::value == true);
        CHECK(my::is_array<int[10]>::value == true);
        CHECK(my::is_array<std::array<int, 10>>::value == false);
    }
    
    SECTION("Check my::is_pointer")
    {
        struct A
        {
            int m;
            void fn() {}
        };
        
        int A::*member_data_ptr = &A::m;
        [[maybe_unused]] void (A::*member_fn_ptr)() = &A::fn;
        
        CHECK(my::is_pointer<A>::value == false);
        CHECK(my::is_pointer_v<A> == false);
        CHECK(my::is_pointer<A>() == false);    // 调用继承的 constexpr bool my::integral_const<bool, false>::operator bool() const noexcept
        CHECK(my::is_pointer<A>{} == false);    // 同上
        CHECK(my::is_pointer<A>()() == false);
        CHECK(my::is_pointer<A>{}() == false);  // 调用继承的 constexpr bool my::integral_constant<bool, false>::operator()() const noexcept
        
        CHECK(my::is_pointer<A*>::value == true);
        CHECK(my::is_pointer_v<A const* volatile> == true);
        CHECK(my::is_pointer_v<A&> == false);
        
        bool is_data_ptr = my::is_pointer<decltype(member_data_ptr)>::value;
        CHECK(is_data_ptr == false);
        
        bool is_fn_ptr = my::is_pointer<decltype(member_fn_ptr)>::value;
        CHECK(is_fn_ptr == false);
        
        CHECK(my::is_pointer_v<void*> == true);
        CHECK(my::is_pointer_v<int> == false);
        CHECK(my::is_pointer_v<int*> == true);
        CHECK(my::is_pointer_v<int**> == true);
        
        CHECK(my::is_pointer_v<int[10]> == false);
        CHECK(my::is_pointer_v<std::nullptr_t> == false);
        CHECK(my::is_pointer_v<void (*)()> == true);
    }
    
    SECTION("Utilize the my::is_union")
    {
        struct A {};
        CHECK(my::is_union_v<A> == false);
        
        typedef union
        {
            int a;
            float b;
        } BUnion;
        CHECK(my::is_union<BUnion>::value == true);
        
        struct C
        {
            BUnion bun;
        };
        CHECK(my::is_union_v<C> == false);
        CHECK(my::is_union<int>::value == false);
    }
    
    SECTION("Check my::is_class")
    {
        struct A {};
        CHECK(my::is_class<A>::value == true);
        
        class B {};
        CHECK(my::is_class<B>::value == true);
        CHECK(my::is_class_v<B*> == false);
        CHECK(my::is_class_v<B&> == false);
        CHECK(my::is_class_v<const B> == true);
        
        enum class E {};
        CHECK(my::is_class_v<E> == false);
        
        union U
        {
            class UC {};
        };
        CHECK(my::is_class<U>::value == false);
        CHECK(my::is_class_v<U::UC> == true);
        
        CHECK(my::is_class_v<int> == false);
        CHECK(my::is_class_v<struct S> == true);
        CHECK(my::is_class_v<class C> == true);
    }
    
    SECTION("Check my::is_function")
    {
        int fn();
        CHECK(my::is_function<decltype(fn)>::value == true);
        
        CHECK(my::is_function<int(int)>::value == true);
        CHECK(my::is_function<int>::value == false);
        CHECK(my::is_function<decltype([] {})>::value == false);     // for lambda expression
        CHECK(my::is_function<std::function<void()>>::value == false);
        
        struct Functor
        {
            void operator()()
            {
            }
        };
        CHECK(my::is_function<Functor()>::value == true);
        
        struct A
        {
            static int foo();
            int func() const &;
        };
        CHECK(my::is_function<A>::value == false);
        CHECK(my::is_function<decltype(A::foo)>::value == true);
        CHECK(my::is_function<decltype(&A::func)>::value == false);
        
        using T = PM_traits<decltype(&A::func)>::member_type;
        CHECK(my::is_function<T>::value == true);
    }
    
    SECTION("Check my::is_const")
    {
        CHECK(my::is_same_v<const int*, int const*> == true);
        CHECK((my::is_const<int>::value == false && my::is_const<const int>::value == true));
        CHECK((my::is_const<int*>::value == false &&
               my::is_const<int* const>::value == true &&
               my::is_const<const int*>::value == false));
        CHECK(my::is_const<const int&>::value == false);
        // CHECK(my::is_const<int& const>::value == true);     // 'const' qualifier cannot be applied to a reference.
        CHECK(my::is_const<my::remove_reference_t<const int&>>::value == true);
        
        struct S
        {
            void foo() const {}
            void bar() const {}
        };
        CHECK(my::is_const<decltype(&S::foo)>::value == false);
        
        using S_mem_func_ptr = void (S::*)() const;
        S_mem_func_ptr foo_ptr = &S::foo;
        CHECK(my::is_const<decltype(foo_ptr)>::value == false);
        
        foo_ptr = &S::bar;  // OK, the same one pointer can be re-pointed
        CHECK(my::is_const<decltype(foo_ptr)>::value == false);
        
        const S_mem_func_ptr cfn_ptr = &S::foo;
        CHECK(my::is_const<decltype(cfn_ptr)>::value == true);
    }
    
    SECTION("Check my::is_volatile")
    {
        CHECK(my::is_volatile<int>::value == false);
        CHECK(my::is_volatile<volatile int>::value == true);
        CHECK(my::is_volatile<volatile const int>::value == true);
        CHECK(my::is_volatile<volatile std::valarray<float>>::value == true);
        CHECK(my::is_volatile<std::valarray<volatile int>>::value == false);
    }
    
    SECTION("Check my::is_lvalue_reference and my::is_rvalue_reference")
    {
        class A {};
        CHECK(my::is_lvalue_reference<A>::value == false);
        CHECK(my::is_lvalue_reference<A&>::value == true);
        CHECK(my::is_lvalue_reference<A&&>::value == false);
        CHECK(my::is_lvalue_reference<int>::value == false);
        CHECK(my::is_lvalue_reference<int&>::value == true);
        CHECK(my::is_lvalue_reference<int&&>::value == false);
        
        CHECK(my::is_rvalue_reference<A>::value == false);
        CHECK(my::is_rvalue_reference<A&>::value == false);
        CHECK(my::is_rvalue_reference<A&&>::value == true);
        
        std::cout << "test(42): " << std::endl;
        test(42);
        
        std::cout << "test(x): " << std::endl;
        int x = 42;
        test(x);
    }
    
    SECTION("Check my::is_constructible")
    {
        class Foo
        {
            int v1;
            double v2;
        public:
            Foo(int n) : v1{n}, v2{}
            {
            }
            Foo(int n, double f) noexcept : v1{n}, v2{f}
            {
            }
        };
        CHECK(my::is_trivially_constructible<Foo, const Foo&>::value == true);
        CHECK(my::is_trivially_constructible<Foo, int>::value == false);
        CHECK(my::is_constructible<Foo, int>::value == true);
        CHECK(my::is_nothrow_constructible<Foo, int>::value == false);
        CHECK(my::is_nothrow_constructible<Foo, int, double>::value == true);
        
        struct S1
        {
            std::string str;    // member has a non-trivial default constructor
        };
        CHECK(my::is_default_constructible<S1>::value == true);
        CHECK(my::is_trivially_default_constructible<S1>::value == false);
        
        struct S2
        {
            int n;
            S2() = default;     // trivial and no-throwing
        };
        CHECK(my::is_trivially_default_constructible<S2>::value == true);
        CHECK(my::is_nothrow_default_constructible<S2>::value == true);
    }
    
    SECTION("Check my::is_copy_constructible")
    {
        struct S1
        {
            std::string str;    // member has a non-trivial copy constructor
        };
        CHECK(my::is_copy_constructible<S1>::value == true);
        CHECK(my::is_trivially_copy_constructible<S1>::value == false);
        
        struct S2
        {
            int n;
            S2(const S2&) = default;    // trivial and no-throwing
        };
        CHECK(my::is_trivially_copy_constructible<S2>::value == true);
        CHECK(my::is_nothrow_copy_constructible<S2>::value == true);
        
        struct S3
        {
            S3(const S3&) = delete;     // explicitly deleted
        };
        CHECK(my::is_copy_constructible<S3>::value == false);
        
        struct S4
        {
            S4(S4&) {}  // cannot bind const, hence not a copy-constructible
        };
        CHECK(my::is_copy_constructible<S4>::value == false);
    }
    
    SECTION("Check my::is_move_constructible")
    {
        struct Ex1
        {
            std::string str;    // member has a non-trivial but non-throwing move constructor
        };
        CHECK(my::is_move_constructible<Ex1>::value == true);
        CHECK(my::is_trivially_move_constructible<Ex1>::value == false);
        CHECK(my::is_nothrow_move_constructible<Ex1>::value == true);
        
        struct Ex2
        {
            int n;
            Ex2(Ex2&&) = default;   // trivial and non-throwing
        };
        CHECK(my::is_move_constructible<Ex2>::value == true);
        CHECK(my::is_trivially_move_constructible<Ex2>::value == true);
        CHECK(my::is_nothrow_move_constructible<Ex2>::value == true);
        
        struct NoMove1
        {
            /*!
             *  \attention  this class prevents from implicit declaration of default move constructor;
             *              however, it is still move-constructible, because its copy constructor can bind to an rvalue argument.
             */
            NoMove1(const NoMove1&) {}
        };
        CHECK(my::is_move_constructible<NoMove1>::value == true);
        CHECK(my::is_trivially_move_constructible<NoMove1>::value == false);
        CHECK(my::is_nothrow_move_constructible<NoMove1>::value == false);
        
        struct NoMove2
        {
            /*!
             *  \details    Not move-constructible since the lvalue reference cannot bind to the rvalue argument.
             */
            NoMove2(NoMove2&) {}
        };
        CHECK(my::is_move_constructible<NoMove2>::value == false);
        CHECK(my::is_trivially_move_constructible<NoMove2>::value == false);
        CHECK(my::is_nothrow_move_constructible<NoMove2>::value == false);
    }
    
    SECTION("Check my::is_assignable")
    {
        struct Ex
        {
            int n;
        };
        CHECK(my::is_assignable<int, int>::value == false);     // 1 = 1; wouldn't compile
        CHECK(my::is_assignable<int&, int>::value == true);     // int a; a = 1; can work
        CHECK(my::is_assignable<int, double>::value == false);
        CHECK(my::is_trivially_assignable<int&, double>::value == true);
        CHECK(my::is_assignable<std::string, double>::value == true);
        CHECK(my::is_trivially_assignable<Ex&, const Ex&>::value == true);
    }
    
    SECTION("Check my::is_copy_assignable")
    {
        struct Foo
        {
            int n;
        };
        CHECK(my::is_copy_assignable<int[2]>::value == false);
        CHECK(my::is_trivially_copy_assignable<Foo>::value == true);
        CHECK(my::is_nothrow_copy_assignable<int>::value == true);
    }
    
    SECTION("Check my::is_move_assignable")
    {
        struct Foo
        {
            int n;
        };
        struct NoMove
        {
            NoMove& operator=(const NoMove&)
            {
                return *this;
            }
        };
        CHECK(my::is_nothrow_move_assignable<std::string>::value == true);
        CHECK(my::is_move_assignable<int[2]>::value == false);
        CHECK(my::is_trivially_move_assignable<Foo>::value == true);
        CHECK(my::is_move_assignable<NoMove>::value == true);
        CHECK(my::is_nothrow_move_assignable<NoMove>::value == false);
    }
    
    SECTION("Check my::is_destructible")
    {
        struct Foo
        {
            std::string str;
            ~Foo() noexcept
            {
            }
        };
        struct Bar
        {
            ~Bar() = default;
        };
        CHECK(my::is_destructible<std::string>::value == true);
        CHECK(my::is_nothrow_destructible<Foo>::value == true);
        CHECK(std::is_trivially_destructible<Foo>::value == false);
        CHECK(std::is_trivially_destructible<Bar>::value == true);
    }
    
    SECTION("Check my::has_virtual_destructor")
    {
        CHECK(my::has_virtual_destructor<int>::value == false);
        
        struct S {};
        CHECK(my::has_virtual_destructor<S>::value == false);
        
        class Base
        {
        public:
            virtual ~Base();
        };
        class Derived : public Base
        {
        public:
            ~Derived();
        };
        CHECK(my::has_virtual_destructor<Derived>::value == true);
    }
    
    SECTION("Check my::is_base_of")
    {
        class A {};
        class B : public A {};
        class C : public B {};
        class D {};
        union E {};
        using I = int;
        
        CHECK(my::is_base_of<A, A>::value == true);
        CHECK(my::is_base_of<A, B>::value == true);
        CHECK(my::is_base_of<A, C>::value == true);
        CHECK(my::is_base_of<A, D>::value == false);
        CHECK(my::is_base_of<B, A>::value == false);
        CHECK(my::is_base_of<E, E>::value == false);
        CHECK(my::is_base_of<I, I>::value == false);
    }
    
    SECTION("Check my::is_convertible")
    {
        class A
        {
        public:
            virtual ~A() = default;
        };
        class B : public A
        {
        public:
            B() : A()
            {
            }
            ~B() = default;
        };
        class C
        {
        };
        class D
        {
        public:
            operator C()
            {
                return c;
            }
            C c;
        };
        
        CHECK( my::is_convertible<B*, A*>::value == true);
        CHECK(std::is_convertible<B*, A*>::value == true);
        
        CHECK( my::is_convertible<A*, B*>::value == false);
        CHECK(std::is_convertible<A*, B*>::value == false);
        
        CHECK( my::is_convertible<D, C>::value == true);
        CHECK(std::is_convertible<D, C>::value == true);
        
        CHECK( my::is_convertible<B*, C*>::value == false);
        CHECK(std::is_convertible<B*, C*>::value == false);
        
        CHECK( my::is_convertible<A, E>::value == true);
        CHECK(std::is_convertible<A, E>::value == true);
        
        CHECK( my::is_convertible<std::string_view, std::string>::value == false);
        CHECK(std::is_convertible<std::string_view, std::string>::value == false);
        
        CHECK( my::is_convertible<std::string, std::string_view>::value == true);
        CHECK(std::is_convertible<std::string, std::string_view>::value == true);
        
        auto stringify = []<typename T>(T x)
        {
            if constexpr ( my::is_convertible<T, std::string>::value or  my::is_convertible<T, std::string_view>::value)
         // if constexpr (std::is_convertible<T, std::string>::value or std::is_convertible<T, std::string_view>::value)
            {
                return x;
            }
            else
            {
                return std::to_string(x);
            }
        };
        
        using std::operator "" s, std::operator "" sv;
        const char* three = "three";
        
        std::cout << std::quoted(stringify("one"s)) << std::endl
                  << std::quoted(stringify("two"s)) << std::endl
                  << std::quoted(stringify(three)) << std::endl
                  << std::quoted(stringify(42)) << std::endl
                  << std::quoted(stringify(42.0)) << std::endl;
    }
    
    SECTION("Check my::remove_pointer and my::add_pointer")
    {
        CHECK(my::is_same<int, my::remove_pointer<int>::type>::value == true);
        CHECK(my::is_same<int, my::remove_pointer<int*>::type>::value == true);
        CHECK(my::is_same<int, my::remove_pointer<int**>::type>::value == true);
        CHECK(my::is_same_v<int, my::remove_pointer<int* const>::type> == true);
        CHECK(my::is_same_v<int, my::remove_pointer<int* volatile>::type> == true);
        CHECK(my::is_same_v<int, my::remove_pointer<int* const volatile>::type> == true);
        
        struct S
        {
            void fn_ref() & {}
            void fn_const() const {}
        };
        int i = 123;
        int& ri = i;
        
        using IntPtr = my::add_pointer<decltype(i)>::type;
        using IntPtr2 = my::add_pointer<decltype(ri)>::type;
        
        IntPtr pi = &i;
        std::cout << "i = " << i << std::endl;
        std::cout << "*pi = " << *pi << std::endl;
        CHECK(my::is_pointer<IntPtr>::value == true);
        CHECK(my::is_same<IntPtr, int*>::value == true);
        CHECK(my::is_same<IntPtr2, IntPtr>::value == true);

        using IntAgain = my::remove_pointer<IntPtr>::type;
        IntAgain j = i;
        std::cout << "j = " << j << std::endl;

        CHECK(my::is_pointer<IntAgain>::value == false);
        CHECK(my::is_same<IntAgain, int>::value == true);

        ptr_to_member_func_cvref_test(&S::fn_ref);
        ptr_to_member_func_cvref_test(&S::fn_const);
    }
    
    SECTION("Check my::decay")
    {
        CHECK(is_decay_equal<int, int> == true);
        CHECK(is_decay_equal<int, float> == false);
        CHECK(is_decay_equal<int&, int> == true);
        CHECK(is_decay_equal<int&&, int> == true);
        CHECK(is_decay_equal<const int&, int> == true);
        
        CHECK(is_decay_equal<int[2], int*> == true);
        CHECK(is_decay_equal<int[4][2], int*> == false);
        CHECK(is_decay_equal<int[4][2], int**> == false);
        CHECK(is_decay_equal<int[4][2], int(*)[2]> == true);
        
        CHECK(is_decay_equal<int(int), int (*)(int)> == true);      // 函数的退化类型也是一个函数指针
    }
    
    SECTION("Check my::conditional")
    {
        using Type1 = my::conditional<true, int, double>::type;
        using Type2 = my::conditional<false, int, double>::type;
        using Type3 = my::conditional<sizeof(int) >= sizeof(double), int, double>::type;
        
        std::cout << "Type1 = " << typeid(Type1).name() << std::endl;
        std::cout << "Type2 = " << typeid(Type2).name() << std::endl;
        std::cout << "Type3 = " << typeid(Type3).name() << std::endl;
    }
    
    SECTION("Check my::remove_all_extents")
    {
        float   a0;
        float   a1[1][2][3];
        float   a2[1][2][3][4];
        float   *a3;
        int     a4[3][2];
        double  a5[2][3];
        
        struct X
        {
            int m;
        } x0[3][3];
        
        info(a0);
        info(a1);
        info(a2);
        info(a3);
        info(a4);
        info(a5);
        info(x0);
    }
}
