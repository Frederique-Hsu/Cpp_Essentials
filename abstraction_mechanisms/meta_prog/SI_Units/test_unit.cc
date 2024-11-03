/*!
 *  \file       test_unit.cc
 *  \brief      
 *  
 */


#include "unit.hpp"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(UTest4Unit)

    BOOST_AUTO_TEST_CASE(CheckQuantity)
    {
        Quantity<Meter> x{10.5};    // x is 10.5m
        Quantity<Second> y{2};      // y is 2s
        Quantity<Speed> s{7};

        Quantity<Speed> speed(10);
        [[maybe_unused]] auto double_speed = 2 * speed;
        // [[maybe_unused]] auto increased_speed = 2.3 + speed;

        auto distance = Quantity<Meter>{10};
        auto time = Quantity<Second>{20};
        speed = distance / time;
        BOOST_CHECK(speed == Quantity<Speed>{0.5});
    }

    BOOST_AUTO_TEST_CASE(CheckLiteralUnit)
    {
        auto distance = 10.0_m;
        auto time = 20.0_s;
        auto speed = distance / time;
        BOOST_CHECK(speed == Quantity<Speed>{0.5});

        Quantity<Acceleration> acceleration = distance / square(time);
        std::cout << "speed = " << speed << ", acceleration = " << acceleration << std::endl;
    }

BOOST_AUTO_TEST_SUITE_END()