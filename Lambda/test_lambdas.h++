/*!
 *  \file       test_lambdas.h++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include <vector>

class UTester4LambdaFunctions : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::vector<std::uint64_t> generateFibonacci(int n);

    void userAlgo(std::vector<int>& vec);
};


void UTester4LambdaFunctions::SetUp()
{
}

void UTester4LambdaFunctions::TearDown()
{
}
