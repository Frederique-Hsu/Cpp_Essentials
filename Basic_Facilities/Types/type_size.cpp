/*!
 *  \file       type_size.cpp
 *  \brief      研究C++基本类型的尺寸问题
 *
 */



#include <gtest/gtest.h>
#include <limits>
#include <iostream>
#include <cstdint>
#include <cstddef>

/*!
 *  \warning    C++基本类型的尺寸是依赖于实现的。
 *  \remark     同一个数据类型，在不同硬件平台，不同编译器环境下，其尺寸可能是不同的。
 */


TEST(UTester4CppBasicTypeSize, CheckBasicTypeSize)
{
    ASSERT_TRUE(sizeof(char) == 1);

    EXPECT_EQ(sizeof(wchar_t), 4);
    EXPECT_EQ(sizeof(char16_t), 2);
    EXPECT_EQ(sizeof(char32_t), 4);

    using UTF8 = char;
    using UTF16 = char16_t;
    using UTF32 = char32_t;

    EXPECT_EQ(sizeof(short), 2);
    EXPECT_EQ(sizeof(int), 4);
    EXPECT_EQ(sizeof(long), 8);
    EXPECT_EQ(sizeof(long long), 8);

    EXPECT_EQ(sizeof(bool), 1);

    EXPECT_EQ(sizeof(float), 4);
    EXPECT_EQ(sizeof(double), 8);
    EXPECT_EQ(sizeof(long double), 16);

    EXPECT_EQ(sizeof(int*), 8);
    EXPECT_TRUE(sizeof(int*) == sizeof(void*));
    EXPECT_TRUE(sizeof(int*) == sizeof(double*));
    EXPECT_TRUE(sizeof(int*) == sizeof(long*));

    EXPECT_EQ(sizeof(int16_t), 2);
    EXPECT_EQ(sizeof(int64_t), 8);

    EXPECT_EQ(sizeof(int_least16_t), 2);
    EXPECT_EQ(sizeof(int_least32_t), 4);
    EXPECT_EQ(sizeof(int_fast32_t), 8);
}

TEST(UTester4CppBasicTypeSize, CheckTypeLimits)
{
    using namespace std;

    cout << "size of long = " << sizeof(1L) << endl;
    cout << "size of long long = " << sizeof(1LL) << endl;

    cout << "largest float = " << std::numeric_limits<float>::max() << endl;
    cout << "smallest int = " << std::numeric_limits<int>::min() << endl;
    cout << "largest unsigned int = " << std::numeric_limits<unsigned int>::max() << endl;
    cout << "char is signed? " << std::numeric_limits<char>::is_signed << endl;
}

/*================================================================================================*/
/*!
 *  \brief      空基类
 */
class CEmptyBase
{
};

struct SEmptyBase
{
};

TEST(UTester4EmptyBaseClass, CheckEmptyBaseClassSize)
{
    using namespace std;

    cout << "Size of empty base class = " << sizeof(CEmptyBase) << endl;
    cout << "Size of empty base struct = " << sizeof(SEmptyBase) << endl;
}

/*!
 *  \brief      空基类优化
 */
class CMyPublicConcrete : public CEmptyBase
{
private:
    int number;
public:
    CMyPublicConcrete() : number{0} {}
};

class CMyPrivateConcrete : private CEmptyBase
{
private:
    int number;
public:
    CMyPrivateConcrete() : number{0} {}
};

TEST(UTester4EBO, CheckHowEBOWorks)
{
    using namespace std;
    cout << "sizeof(CMyPublicConcrete) = " << sizeof(CMyPublicConcrete) << endl;
    cout << "sizeof(CMyPrivateConcrete) = " << sizeof(CMyPrivateConcrete) << endl;

    class CMyPublicEmptyConcrete : public CEmptyBase
    {
    public:
        CMyPublicEmptyConcrete() {}
    };
    cout << "sizeof(CMyPublicEmptyConcrete) = " << sizeof(CMyPublicEmptyConcrete) << endl;

    class CMyPrivateEmptyConcrete : private CEmptyBase
    {
    public:
        CMyPrivateEmptyConcrete() {}
    };
    cout << "sizeof(CMyPrivateEmptyConcrete) = " << sizeof(CMyPrivateEmptyConcrete) << endl;
}


/*================================================================================================*/
/*!
 *  \brief      对象的内存对齐
 */
template<typename T>
void user(const std::vector<T>& numbers)
{
    constexpr int bufmax = 1024;
    alignas(T) T buffer[bufmax];    /* 未初始化 */

    const int max = std::min(numbers.size(), bufmax/sizeof(T));
    std::uninitialized_copy(numbers.begin(), numbers.begin()+max, buffer);
}

TEST(UTester4Alignment, CheckHowToAlignObjects)
{
    auto ac = alignof(char);     /* char的对齐情况 */
    auto ai = alignof(1);       /* int的对齐情况 */
    auto ad = alignof(2.0);     /* double的对齐情况 */

    std::cout << ac << "\t" << ai << "\t" << ad << std::endl;
}
