/*!
 *  \file       test_arguments.h++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include <alloca.h>

/*!
 *  \section        Prototypes
 */
class UTest4Arguments : public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;

protected:
    std::vector<int> m_fibonacci;
    int* m_numbers;

private:
    void prepareTestData();
    void allocNumbers(std::size_t n);
    void deallocNumbers();
};


/*!
 *  \section        Implementations
 */
void UTest4Arguments::prepareTestData()
{
    m_fibonacci.resize(20U);

    m_fibonacci[0] = 1;
    m_fibonacci[1] = 1;

    for (auto index = 2U; index < m_fibonacci.size(); ++index)
    {
        m_fibonacci[index] = m_fibonacci[index-1] + m_fibonacci[index-2];
    }
}

void UTest4Arguments::SetUp()
{

}

void UTest4Arguments::TearDown()
{

}

void UTest4Arguments::allocNumbers(std::size_t n)
{
    (void)n;
}

void UTest4Arguments::deallocNumbers()
{
}
