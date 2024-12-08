/*!
 *  \file       test_parallel_accumulate.h++
 *  \brief      Make a unit test to validate the accumulating elements of a huge container
 *              in parallel, by using the packaged_task.
 *  \author     Frederique Hsu
 *
 */


#pragma once

#include <gtest/gtest.h>
#include <vector>

class UTester4ParallelAccumulator : public ::testing::Test
{
protected:
    std::vector<double> random_numbers;
public:
    UTester4ParallelAccumulator();
    ~UTester4ParallelAccumulator() {}
public:
    void SetUp() override;
    void TearDown() override;
};
