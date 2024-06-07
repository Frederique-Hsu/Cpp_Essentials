/*!
 *  \file       test_type_conversion.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <cmath>
#include <complex>

#include "explicit_type_conversion.hpp"

TEST(UTest4TypeConversion, CheckImplicitTypeConversion)
{
    double d = int{123456};     // 整数转换成浮点数，根据语言的规则，隐式转换的。
    int i = d;                  // 浮点数转换成整数，也是隐式转换，自动进行的。

    EXPECT_EQ(typeid(d), typeid(double));
    EXPECT_EQ(typeid(i), typeid(int));

    EXPECT_EQ(i, d);
}

TEST(UTest4TypeConversion, CheckNarrowCast)
{
    double d = int{123456};

#if true
    EXPECT_NO_THROW({
        int i = narrow_cast<int>(d);
    });
#else
    EXPECT_THROW({
                    int i = narrow_cast<int>(d);
                 },
                 std::runtime_error);
#endif

    auto test = [](double d, int i, char* p) -> void {
        EXPECT_NO_THROW({
                            auto c1 = narrow_cast<char>(64);
                            std::cout << "c1 = " << c1 << std::endl;
                        });
        EXPECT_THROW({
                         auto c2 = narrow_cast<unsigned char>(-64);
                         std::cout << "c2 = " << c2 << std::endl;
                     },
                     std::runtime_error);
        EXPECT_THROW({
                        auto c3 = narrow_cast<char>(264);
                        std::cout << "c3 = " << c3 << std::endl;
                     },
                     std::runtime_error);

        EXPECT_NO_THROW({
                            auto d1 = narrow_cast<double>(1 / 3.0F);
                            std::cout << "d1 = " << d1 << std::endl;
                        });
        EXPECT_THROW({
                         auto f1 = narrow_cast<float>(1 / 3.0);
                         std::cout << "f1 = " << f1 << std::endl;
                     },
                     std::runtime_error);

        EXPECT_NO_THROW({
                            auto c4 = narrow_cast<char>(i);
                            std::cout << "c4 = " << c4 << std::endl;
                        });
        EXPECT_NO_THROW({
                            auto f2 = narrow_cast<float>(d);
                            std::cout << "f2 = " << std::setw(10) << std::setprecision(4) << f2 << std::endl;
                        });

        // auto p1 = narrow_cast<char*>(i);    // Compilation error: invalid "static_cast" from "int" to "char*"
        // auto i1 = narrow_cast<int>(p);      // Compilation error: invalid "static_cast" from "char*" to "int"

        EXPECT_NO_THROW({
                            double d2 = narrow_cast<double>(i);
                            std::cout << "d2 = " << d2 << std::endl;
                        });
        EXPECT_NO_THROW({
                            auto i2 = narrow_cast<int>(d);
                            std::cout << "i2 = " << i2 << std::endl;
                        });
    };

    char love[] = {'l', 'o', 'v', 'e'};
    test(d, 105, love);
}

void f(int i)
{
    std::cout << "called f(int " << i << ")" << std::endl;
}
void f(double d)
{
    std::cout << "called f(double " << d << ")" << std::endl;
}

TEST(UTest4TypeConversion, CheckConstructionCast)
{
    /*!
     *  \note   构造转换， 用值e构建一个类型为T的值可以表示为T{e}.
     *          符号T{v}有一个好处，就是它只执行“行为良好的”类型转换.
     */
    auto g = [](int i, double d) {
        f(i);
        // f(double{i});                        // 错误： {}拒绝执行整数向浮点数的类型转换
        f(d);
        // f(int{d});                           // 错误： {}拒绝截断的行为
        f(static_cast<int>(d));                 // OK: 调用f(int)，但传入的是个截断的值
        f(std::round(d));                       // OK: 调用f(double)
        f(static_cast<int>(std::lround(d)));    // OK: 调用f(int)
    };

    g(5, 3.1415926);
}

TEST(UTest4TypeConversion, NotAllowedConstructionCastFromIntToDouble)
{
    int i = 12345;
    // f(double{i});   // Error: Non-constant-expression cannot be narrowed from type "int" to "double" in the initializer-list

    /*!
     *  \warning    {}构造不允许int向double转换，是因为：
     *              在某些体系结构中，int与double所占的位数可能一样，则其中的某些int向double转换必将损失信息。
     *              如下情形：
     */
    // static_assert(sizeof(int) == sizeof(double), "unexpected sizes");    // 若int与double所占位数一样
    int x = std::numeric_limits<int>::max();    // x取最大值
    double d = x;   // 则此时d就可能损失信息
    int y = x;

    EXPECT_DOUBLE_EQ(d, x);
    EXPECT_EQ(y, x);

#if false
    auto g = [](char* p) -> void {
        /*!
         *  \warning    一旦我们在程序中使用目标类型作为显式的限定，则在这种情况下就
         *              不允许行为不正常的类型转换了。
         */
        int x = int{p};

        using Pint = int*;
        int* p2 = Pint{p};
    };
#endif
}

TEST(UTest4TypeConversion, ConstructorDefaultValue)
{
    /*!
     *  \note   构造函数符号T{}用于表示类型的默认值
     *
     *          对于内置类型来说，显式使用其构造函数得到的值是该类型对应的0值
     *          对于用户自定义类型T来说，如果含有默认构造函数，则T{}的结果由默认构造函数来定义；否则，由每个成员的默认构造函数MT{}来定。
     *
     *          显式构造的未命名对象是临时对象，而且其生命周期仅限于其所在的完整表达式。
     *          在这一点上，他们也通过new创建的未命名对象是有区别的。
     */
    fn(int{});      // 默认的int值 0
    fn(std::complex<double>{});     // 默认的complex值 {0, 0}
}

TEST(UTest4TypeConversion, CheckTypeSize)
{
#pragma pack(1)     // 按用户指定的n个字节对齐
    typedef struct Align
    {
        std::uint8_t    a;
        std::uint16_t   b;
        std::uint32_t   c;
    } Align;
#pragma pack()      // 取消用户定义的字节对齐，要成对使用

/*================================================================================================*/

#define SAME_ADJACENT_TYPE_LESS_THAN_TYPESIZE       1
#define SAME_ADJACENT_TYPE_GREAT_THAN_TYPESIZE      2
#define DIFF_ADJACENT_TYPE_COMPRESSED               3
#define DIFF_INTERLACED_TYPE_UNCOMPRESSED           4
#define BIT_FIELD_TYPE_SIZE                         DIFF_ADJACENT_TYPE_COMPRESSED

    typedef struct BitField
    {
#if (BIT_FIELD_TYPE_SIZE == SAME_ADJACENT_TYPE_LESS_THAN_TYPESIZE)
        /*!
         *  \remark 如果相邻位域字段的类型相同，且其位宽之和小于类型的sizeof大小的，则后面的字段将紧邻前一个字段存储，
         *          凑成一个完整类型。或者直到不能容纳为止。
         */
        char    a:2;
        char    b:4;
#elif (BIT_FIELD_TYPE_SIZE == SAME_ADJACENT_TYPE_GREAT_THAN_TYPESIZE)
        /*!
         *  \remark 如果相邻位域字段的类型相同，但其位宽之和大于类型的sizeof大小，则后面的字段从新的存储单元开始，
         *          其偏移量为类型大小的整数倍。
         */
        char    a:2;
        char    b:8;
#elif (BIT_FIELD_TYPE_SIZE == DIFF_ADJACENT_TYPE_COMPRESSED)
        /*!
         *  \remark 如果相邻的位域字段的类型不同，VC采取不压缩的方式（不同位域字段存放在不同的类型字节中），
         *          GCC采取压缩的方式，凑成较大类型的字段的整数倍大小。
         */
        char    a:2;
        int     b:4;
#elif (BIT_FIELD_TYPE_SIZE == DIFF_INTERLACED_TYPE_UNCOMPRESSED)
        /*!
         *  \remark 如果位域字段之间穿插着非位域字段，所有编译器都不压缩，按照普通字节对齐方式存放各字段。
         */
        char    a:2;
        double  b;
        int     c:4;
#endif
    } BitField;

/*================================================================================================*/

    class EmptyClass
    {
    public:
        EmptyClass() {}
        ~EmptyClass() {}
        EmptyClass(const EmptyClass&) = delete;
        EmptyClass& operator=(const EmptyClass&) = delete;
        EmptyClass(EmptyClass&&) = delete;
        EmptyClass& operator=(EmptyClass&&) = delete;
    private:
    };

    struct EmptyStruct
    {
    };

    class EmptyClass_with_virtual
    {
    public:
        EmptyClass_with_virtual() {}
        virtual ~EmptyClass_with_virtual() {}
    private:
    };

    class Interface
    {
    public:
        virtual void run() = 0;
        virtual bool check() const = 0;
    };

    class Concrete
    {
    public:
        explicit Concrete(int num) : m_num(num) { m_num++; }
        ~Concrete() {}
    private:
        int m_num;
    };

    class Concrete_with_virtual
    {
    public:
        explicit Concrete_with_virtual(int num) : m_num(num) { m_num++; }
        virtual ~Concrete_with_virtual() {}
    private:
        int m_num;
    };

    class RefConcrete
    {
    public:
        explicit RefConcrete(int& num) : m_num(num) { m_num++; }
        ~RefConcrete() {}
    private:
        int& m_num;
    };

    class ConcreteDerived : public EmptyClass
    {
    public:
        explicit ConcreteDerived(int num) : EmptyClass(), m_num(num) { m_num++; }
        ~ConcreteDerived() {}
    private:
        int m_num;
    };

/*================================================================================================*/

    std::cout << "sizeof(int) = " << sizeof(int) << std::endl
              << "sizeof(float) = " << sizeof(float) << std::endl
              << "sizeof(double) = " << sizeof(double) << std::endl
              << "sizeof(long int) = " << sizeof(long int) << std::endl
              << "sizeof(long double) = " << sizeof(long double) << std::endl
              << "sizeof(long long int) = " << sizeof(long long int) << std::endl
              // << "sizeof(long long double) = " << sizeof(long long double) << std::endl   // "long long double" is invalid
              // << "sizeof(long float) = " << sizeof(long float) << std::endl               //  "long float" is invalid
              << "sizeof(std::size_t) = " << sizeof(std::size_t) << std::endl
              << "sizeof(size_t) = " << sizeof(size_t) << std::endl
              // << "sizeof(void) = " << sizeof(void) << std::endl     // sizeof(void) is invalid
              << "sizeof(void*) = " << sizeof(void*) << std::endl
              // << "sizeof(long void*) = " << sizeof(long void*) << std::endl         // "long void*" is invalid
              << "sizeof(char) = " << sizeof(char) << std::endl
              << "sizeof(std::uint8_t) = " << sizeof(std::uint8_t) << std::endl
              << "sizeof(short) = " << sizeof(short) << std::endl
              << "sizeof(std::uint16_t) = " << sizeof(std::uint16_t) << std::endl
              << "sizeof(std::uint32_t) = " << sizeof(std::uint32_t) << std::endl
              << "sizeof(std::uint64_t) = " << sizeof(std::uint64_t) << std::endl
              << "sizeof(EmptyClass) = " << sizeof(EmptyClass) << std::endl
              << "sizeof(EmptyStruct) = " << sizeof(EmptyStruct) << std::endl
              << "sizeof(EmptyClass_with_virtual) = " << sizeof(EmptyClass_with_virtual) << std::endl
              << "sizeof(Interface) = " << sizeof(Interface) << std::endl
              << "sizeof(Concrete) = " << sizeof(Concrete) << std::endl
              << "sizeof(Concrete_with_virtual) = " << sizeof(Concrete_with_virtual) << std::endl
              << "sizeof(RefConcrete) = " << sizeof(RefConcrete) << std::endl
              << "sizeof(ConcreteDerived) = " << sizeof(ConcreteDerived) << std::endl      // because of EOB
              << "sizeof(Align) = " << sizeof(Align) << std::endl
              << "sizeof(BitField) = " << sizeof(BitField) << std::endl;
}
