/*!
 *  \file       test_algorithm_with_function_pointer.h++
 *  \brief
 *
 */


#pragma once

#include <gtest/gtest.h>

class UTest4FunctionPointerAlgorithm : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

    void displayFibonacciArray();
protected:
    const size_t N = 30;

    std::uint64_t* m_fib_array;
private:
    void prepareShuffledFibonacciArray();
};
