/*!
 *  \file       test_tuple.cc
 *  \brief      
 *  
 */


#include "tuple.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(UTest4Tuple)

    BOOST_AUTO_TEST_CASE(InstantiateTuple4Types)
    {
        Tuple<double, std::string, int, char> object{3.14, std::string("Alice"), 127, 'h'};
        std::cout << "sizeof(std::string(\"Alice\")) = " << sizeof(std::string("Alice")) << std::endl;
        std::cout << "sizeof(Tuple) = " << sizeof(object) << std::endl;

        std::cout << object << std::endl;

        auto element = get<2>(object);
        BOOST_CHECK(typeid(element) == typeid(int));
        BOOST_CHECK_EQUAL(element, 127);
    }

    BOOST_AUTO_TEST_CASE(CheckTupleMemoryLayout)
    {
        class FO {};    // empty class
        typedef Tuple<int*, int*> T0;
        typedef Tuple<int*, FO> T1;
        typedef Tuple<int*, FO, FO> T2;

        std::cout << "sizeof(FO) = " << sizeof(FO) << std::endl
                  << "sizeof(T0) = " << sizeof(T0) << std::endl
                  << "sizeof(T1) = " << sizeof(T1) << std::endl
                  << "sizeof(T2) = " << sizeof(T2) << std::endl;    // empty base optimization
    }

    BOOST_AUTO_TEST_CASE(CheckMakeTuple)
    {
        auto tuple = Make_Tuple<double, std::string, int, std::vector<char>>(
            3.1415926, std::string("Alice"), 125, std::vector<char>{'h', 'e', 'l', 'l', 'o'});
        
        BOOST_CHECK(typeid(tuple) == typeid(Tuple<double, std::string, int, std::vector<char>>));
        BOOST_CHECK(get<0>(tuple) == 3.1415926 );
        BOOST_CHECK(get<1>(tuple) == std::string("Alice"));
        BOOST_CHECK(get<2>(tuple) == 125);
        BOOST_CHECK(get<3>(tuple).size() == 5);
    }

BOOST_AUTO_TEST_SUITE_END()