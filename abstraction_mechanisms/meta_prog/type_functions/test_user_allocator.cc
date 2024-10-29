/*!
 *  \file       test_user_allocator.cc
 *  \brief
 *
 */


#include "user_allocator.hpp"
#include "user_allocator.cpp"


#include <boost/test/unit_test.hpp>

#include <array>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <bitset>
#include <typeindex>


BOOST_AUTO_TEST_SUITE(UTest4UserAllocator)

    #define USE_TYPE_ALIAS

    BOOST_AUTO_TEST_CASE(CheckObjHolderToUniformlyAllocateForObject)
    {
    #if defined(USE_TYPE_ALIAS)
        Holder<double> v1;
        Holder<std::array<double, 200>> v2;
    #else
        typename ObjHolder<double>::type v1;                    // 在栈中分配double
        typename ObjHolder<std::array<double, 200>>::type v2;   // 在堆中分配array
    #endif

        *v1 = 7.7;
        v2->at(77) = 9.9;

        BOOST_CHECK(sizeof(v1) == sizeof(double));

        std::cout << "sizeof(float) = " << sizeof(float) << std::endl
                  << "sizeof(double) = " << sizeof(double) << std::endl
                  << "sizeof(long double) = " << sizeof(long double) << std::endl
                  << "sizeof(double*) = " << sizeof(double*) << std::endl
                  << "sizeof(std::array<double, 200>) = " << sizeof(std::array<double, 200>) << std::endl
                  << "sizeof(v1) = " << sizeof(v1) << std::endl
                  << "sizeof(v2) = " << sizeof(v2) << std::endl;

        // std::cout << "typeof(v1) = " << std::type_index(typeid(v1)).name() << std::endl;
        // std::cout << "typeof(v2) = " << typeid(v2).name() << std::endl;

        // BOOST_CHECK(sizeof(v2) == sizeof(std::array<double, 200>));
    }

    BOOST_AUTO_TEST_CASE(CheckWhenNotAdoptTypeAlias)
    {
        /*!
         *  \note   Make_Unsigned 类型别名 用于返回对应的无符号类型。
         *          当试图将其用于一个非整数类型，例如 std::string， 其实就是在尝试获取一个不存在的类型，结果就是会得到一个编译错误。
         */
        // Make_Unsinged<std::string> unsigned_obj;     // compilation error, because std::string cannot be converted to a unsigned type.
        MyType<int> unsigned_obj;   // OK: int type can be casted to unsigned type

        std::int16_t signed_value = 0b0111'1111'1111'1111;    // binary integer literals are a C++14 extension.
        std::cout << std::bitset<16>(signed_value + 1) << std::endl;
        std::cout << (std::int16_t)(signed_value + 1) << std::endl;

        MyConditionalType<std::int16_t> unsigned_value = 0b0111'1111'1111'1111;
        BOOST_CHECK(typeid(unsigned_value) == typeid(std::uint16_t));

        std::cout << unsigned_value + 1 << std::endl;     
        BOOST_CHECK(unsigned_value + 1 == 0b1000'0000'0000'0000);   
    }

BOOST_AUTO_TEST_SUITE_END()