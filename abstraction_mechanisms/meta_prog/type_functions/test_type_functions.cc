/*!
 *  \file       test_type_functions.cc
 *  \brief
 *
 */


#include <boost/test/unit_test.hpp>

#include "type_functions.hpp"

#include <type_traits>
#include <typeinfo>


BOOST_AUTO_TEST_SUITE(UTest4TypeFunctions)

    BOOST_AUTO_TEST_CASE(CheckIsPolymorphic)
    {
        if (std::is_polymorphic<int>::value)
        {
            std::cout << "Big surprise!" << std::endl;
        }
        else
        {
            std::cout << "Obviously, it is an apparent error." << std::endl;
        }
    }

    BOOST_AUTO_TEST_CASE(CheckUnderlyingType)
    {
        enum class Axis : char
        {
            x,
            y,
            z
        };

        enum flags
        {
            off,
            x = 1,
            y = x << 1,
            z = x << 2,
            t = x << 3
        };

        typename std::underlying_type<Axis>::type xobj;
        typename std::underlying_type<flags>::type yobj;

        BOOST_CHECK(typeid(xobj) == typeid(char));
        BOOST_CHECK(typeid(yobj) == typeid(unsigned int));
        BOOST_CHECK_EQUAL(sizeof(xobj), 1U);
        BOOST_CHECK_EQUAL(sizeof(yobj), 4U);
    }

    BOOST_AUTO_TEST_CASE(CheckUserDefinedType)
    {
        Array3D::type x;
        constexpr int s = Array3D::dim;

        BOOST_CHECK(typeid(x) == typeid(int));
        BOOST_CHECK_EQUAL(s, 3);

        typename Integer<4>::type i4 = 0x0102'0304;     // 4-byte integer
        typename Integer<1>::type i1 = 0x4E;            // 1-byte integer
        BOOST_CHECK(sizeof(i4) == sizeof(int));
        BOOST_CHECK(typeid(i4) == typeid(int));
        BOOST_CHECK(sizeof(i1) == sizeof(signed char));
        BOOST_CHECK(typeid(i1) == typeid(signed char));
    }

BOOST_AUTO_TEST_SUITE_END()