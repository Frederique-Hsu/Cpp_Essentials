/*!
 *  \file       test_my_enable_if.cc
 *  \brief      
 *  
 */


#include <catch2/catch_test_macros.hpp>

#include "my_enable_if.hpp"

#include "test_my_enable_if.hh"

TEST_CASE("Unit Test for SFINAE mechanism", "[SFINAE]")
{
    SECTION("Check how to utilize the SFINAE through my_enable_if")
    {
        printIntegralValue(10);     // OK. T 是 int, is_integral<int>::value 为 true
        
        // 编译错误， T 是 std::string, is_integral<std::string>::value 为 false, 导致替换失败，　函数不参与重载决议。
        // printIntegralValue(std::string("10"));  
        CHECK(true);
    }

    SECTION("Check my::enable_if")
    {
        T iNum(123);
        CHECK(iNum.type == T::int_t);
        T fNum(0.123f);
        CHECK(fNum.type == T::float_t);
    }
    
#if false
    SECTION("Check user's construct() and destroy() functions")
    {
        union
        {
            int i;
            char s[sizeof(std::string)];
        } u;
        
        construct(reinterpret_cast<int*>(&u));

        auto pobj = reinterpret_cast<int*>(&u);
        destroy(pobj);
        
        construct(reinterpret_cast<std::string*>(&u));
        destroy(reinterpret_cast<std::string*>(&u));
        
        Test<int>{};
        Test<double>{};
    }
#endif
}
