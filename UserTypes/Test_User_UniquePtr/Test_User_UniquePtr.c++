/*!
 *  \file       Test_User_UniquePtr.c++
 *  \brief      
 *  
 */


#include "UniquePtr.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Carry out the unit testing for user-defined UniquePtr", "[UniquePtr]")
{    
    SECTION("Check the explicit type conversion for user-define UniquePtr class")
    {
        UniquePtr<int> pointer(new int{9});
        if (!pointer)
        {
            throw std::invalid_argument("Allocating memory for unique_ptr failed.");
        }

        CAPTURE(pointer);
        CHECK(true);
    }
}