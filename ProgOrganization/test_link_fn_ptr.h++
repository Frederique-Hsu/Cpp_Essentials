/*!
 *  \file       test_link_fn_ptr.h++
 *  \brief
 *
 */


#include <CppUTest/TestHarness.h>

TEST_GROUP(UTest4LinkFnPtr)
{
    static constexpr const size_t ARRAY_LENGTH = 20;
    static constexpr const int RANDOM_NUMBER_RANGE = 1001;
public:
    void setup() override;
    void teardown() override;
protected:
    int* array;
private:
    void generateRandomArray();
    void printOut() const;
};
