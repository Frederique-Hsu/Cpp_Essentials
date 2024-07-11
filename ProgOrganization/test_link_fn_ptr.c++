/*!
 *  \file       test_link_fn_ptr.c++
 *  \brief
 *
 */


#include "link_fn_ptr.hpp"

#include "test_link_fn_ptr.h++"

#include <ctime>
#include <iostream>

void TEST_GROUP_CppUTestGroupUTest4LinkFnPtr::setup()
{
    array = new int[ARRAY_LENGTH];
    if (array == nullptr)
    {
        throw std::bad_alloc();
    }

    generateRandomArray();
    std::cout << "\n" << std::endl;
    printOut();
}

void TEST_GROUP_CppUTestGroupUTest4LinkFnPtr::teardown()
{
    if (array != nullptr)
    {
        delete [] array;
    }
}

void TEST_GROUP_CppUTestGroupUTest4LinkFnPtr::generateRandomArray()
{
    std::srand(std::time(NULL));
    for (size_t index = 0; index < ARRAY_LENGTH; ++index)
    {
        *(array + index) = std::rand() % RANDOM_NUMBER_RANGE;
    }
}

void TEST_GROUP_CppUTestGroupUTest4LinkFnPtr::printOut() const
{
    for (size_t index = 0; index < ARRAY_LENGTH; ++index)
    {
        std::printf("% 4d  ", *(array + index));
    }
    std::cout << "\n" << std::endl;
}

TEST(UTest4LinkFnPtr, CheckSortI)
{
    sort_i(array, ARRAY_LENGTH);
}

TEST(UTest4LinkFnPtr, CheckSortX)
{
    sort_x(array, ARRAY_LENGTH);
}

TEST(UTest4LinkFnPtr, CheckSortY)
{
    sort_y(array, ARRAY_LENGTH);
}
