/*!
 *  \file       test_matrix.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>

#include "matrix.hpp"

SCENARIO("Make the unit testing to validate the Matrix<T>", "[matrix]")
{
    GIVEN("Instantiate a Matrix<int> object")
    {
        Matrix<int> matrix(2, 3);

        THEN("Check the size() method of Matrix")
        {
            REQUIRE(matrix.size() == 2 * 3);
        }
    }
}