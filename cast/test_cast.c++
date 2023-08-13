/*!
 *  \file       test_cast.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <cmath>
#include <complex>

#include "cast.hpp"

TEST(UTester4TypeCast, CheckUserDefinedNarrowCast)
{
    double d = 3.1415926;
    int i = 25;

    char word[] = "Hello";
    char* p = word;

    auto c1 = narrow_cast<char>(64);
    std::cout << "c1 = " << c1 << std::endl;

    auto c2 = narrow_cast<char>(-64);           // 如果字符是无符号的，则抛出异常
    std::cout << "c2 = " << c2 << std::endl;

    EXPECT_ANY_THROW(auto c3 = narrow_cast<char>(264));     // 如果字符是8位，则抛出异常

    auto d1 = narrow_cast<double>(1/3.0F);      // OK
    std::cout << "d1 = " << d1 << std::endl;

    EXPECT_THROW(auto f1 = narrow_cast<float>(1/3.0), std::runtime_error);      // 窄化，抛出异常

    auto c4 = narrow_cast<char>(i);
    std::cout << "c4 = " << c4 << std::endl;

    EXPECT_THROW(auto f2 = narrow_cast<float>(d), std::exception);      // 窄化，抛出异常

    // auto p1 = narrow_cast<char*>(i);        // 编译时错误
    auto p1 = reinterpret_cast<char*>(i);       // 而 reinterpret_cast<>() 可进行任意类型之间的转换
    // std::cout << "p1 = " << p1 << std::endl; // 但不能随便使用此转换出来的值，容易崩溃。

    // auto i1 = narrow_cast<int>(p);      // 编译时错误
    auto d2 = narrow_cast<double>(i);
    std::cout << "d2 = " << d2 << std::endl;

    try
    {
        auto i2 = narrow_cast<int>(d);
        std::cout << "i2 = " << i2 << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}


void f(int) {}
void f(double) {}
template<class T> void f(const T&) {}
void g(int i, double d)
{
    f(i);   // 调用f(int)
    // f(double{i});       // 错误： {}拒绝执行证书向浮点数的类型转换
    f(d);   // 调用f(double)
    // f(int{d});      // 错误： {}拒绝截断的行为
    f(static_cast<int>(d));     // 调用f(int), 传入的是个截断的值
    f(std::round(d));           // 调用f(double)，传入的是个四舍五入的值
    f(static_cast<int>(std::lround(d)));    // 调用f(int)，传入的是个四舍五入的值，如果lround(d)溢出int的范围，它仍会被截断。
}
void g(char* p)
{
    // int x = int{p};     // 错误： 不存在char*向int的类型转换

    using Pint = int*;
    // int* p2 = Pint{p};  // 错误： 不存在char*向int*的类型转换
}
void g()
{
    f(int{});   // 默认的int值
    f(std::complex<double>{});      // 默认的complex值
    /*!
     *  \note       对于内置类型来看，显式使用其构造函数得到的值是该类型对应的0值。
     *              因此，int{}可以看成是0的另一种写法。
     *              对于用户自定义类型T来说，如果含有默认构造函数，则T{}的结果由默认构造函数定义；否则，由每个成员
     *              的默认构造函数MT{}定义
     */
}

TEST(UTester4TypeCast, CheckConstructorForTypeCast)
{
    /*!
     *  \warning    用值e构建一个类型为T的值可以表示为T{e}
     *              符号T{v}有一个好处，就是它只执行“行为良好的”类型转换
     */
    auto d1 = double{2};
    double d2{double{2}/4};

    static_assert(sizeof(int) != sizeof(double), "unexpected sizes");

    int x = std::numeric_limits<int>::max();    // 可能的最大整数
    double d = x;
    int y = x;
    std::cout << "x = " << std::hex << x << std::endl
              << "d = " << d << std::endl
              << "y = " << y << std::endl;
    ASSERT_EQ(d, y);
}

void* my_allocator(size_t n)
{
    return std::malloc(n);
}
/*!
 *  \note   命名转换背后隐藏的基本思想是令类型转换的含义更明显，并且让程序员有机会表达他们的真实意图：
 *
 *  \list
 *      \li static_cast 执行关联类型之间的转换，比如一种指针类型向同一个类层次中其他指针类型的转换，或者整数类型向
 *          枚举类型的转换，或者浮点类型向整数类型的转换。它还能执行构造函数和转换运算符定义的类型转换。
 *
 *      \li reinterpret_cast 处理非关联类型之间的转换，比如整数向指针的转换以及指针向另一个非关联指针类型的转换。
 *
 *      \li const_cast 参与转换的类型仅在此const修饰符即volatile修饰符上有所区别
 *
 *      \li dynamic_cast 执行指针或引用向类层次体系的类型转换，并执行运行时检查。
 *  \endlist
 */
TEST(UTester4TypeCast, CheckNamedObjectTypeCasting)
{
    size_t size = 40;
    int* p = static_cast<int*>(my_allocator(size));

    for (size_t i = 0; i < size/(sizeof(p)); i++)
    {
        *(p + i) = std::pow(2, i);
    }
    EXPECT_EQ(*p, 1);
    EXPECT_EQ(*(p+1), 2);
    EXPECT_EQ(*(p+2), 4);
    EXPECT_EQ(*(p+3), 8);

    std::free(p);

    /*============================================================================================*/

    char x = 'a';
    // int* p1 = &x;       // 错误： 不存在char*向int*的隐式类型转换
    // int* p2 = static_cast<int*>(&x);    // 错误：不存在char*向int*的显式类型转换
    int* p3 = reinterpret_cast<int*>(&x);   // 正确，但这种转换非常危险，责任自负。
    EXPECT_NE(*p3, (int)'a');

    class B
    {
    private:
        virtual void execute() { std::cout << "private B::execute()" << std::endl; }
    public:
        B() { std::cout << "B() constructor" << std::endl; }
        virtual ~B() { std::cout << "~B() destructor" << std::endl; }
    };

    class D : public B
    {
    public:
        D() : B() { std::cout << "D() constructor" << std::endl; }
        ~D() { std::cout << "~D() destructor" << std::endl; }
    public:
        void execute() override { std::cout << "public D::execute()" << std::endl; }
    };

    B* pb = new D;      // 正确： D*向B*的隐式类型转换
    // pb->execute();       // 错误： B::execute()是private的，不能调用
    // D* pd = pb;         // 错误： 不存在B*向D*的隐式类型转换
    D* pd = static_cast<D*>(pb);    // 正确
    pd->execute();

    std::cout << "pb = " << std::hex << pb << std::endl
              << "pd = " << pd << std::endl;
    EXPECT_EQ(pb, pd);
    delete pb;

    std::cout << "pd = " << pd << std::endl;
}

TEST(UTester4TypeCast, CheckCStyleTypeCast)
{
    class Base
    {
    private:
        int b;
    public:
        explicit Base(const int& b) : b(b)
        {
            std::cout << "Base() constructor" << std::endl;
        }
        virtual ~Base()
        {
            std::cout << "~Base() destructor" << std::endl;
        }
    public:
        virtual void show_property()
        {
            std::cout << "current property b = " << b << std::endl;
        }
    };

    class Derived : private Base
    {
    private:
        float d;
    public:
        explicit Derived(const int& b, const float& d) : Base(b), d(d)
        {
            std::cout << "Derived() constructor" << std::endl;
        }
        ~Derived()
        {
            std::cout << "~Derived() destructor" << std::endl;
        }
    public:
        void show_property() override
        {
            std::cout << "current property d = " << d << std::endl;
        }
    };

    Derived* child_ptr = new Derived(5, 3.1415);
    child_ptr->show_property();

    /*!
     *  \note   C风格的转换
     *
     *          C++从C继承了符号(T)e， 它可以执行static_cast, reinterpret_cast和const_cast任何组合之后得到的
     *          类型转换，它的含义是从表达式e得到类型为T的值。
     *
     *  \warning    特别警告：C风格的类型转换允许把类的指针转换成指向该类私有基类的指针， 如下的(Base*)child_ptr，
     *              这是一个非常危险的转换操作。切记永远不要这么做。
     *
     *  \note       C风格的类型转换比命名的转换运算符危险得多，原因是我们很难在一个规模交大得程序中定位它，并且不容易
     *              理解程序员真实得类型转换意图。
     *              也就是说，(T)e可能是执行关联类型之间得可移植得类型转换，也可能是非关联类型之间的不可移植的类型转换，
     *              还有可能是移除指针类型前面的const修饰符。由于T和e的类型并不明确，所有我们无法得到确切的结论。
     */
    Base* parent_ptr = (Base*)child_ptr;
    parent_ptr->show_property();

    delete child_ptr;
}

void func(double d, char* p)
{
    /*!
     *  \note       用值e构建类型T的值的过程可以表示为函数形式的符号T(e), 称为函数形式的转换 function-style cast
     *              对于内置类型T来说，T(e)等价于(T)e
     *              这意味着对于大多数内置类型来说，T(e)并不安全。
     *
     *  \remark     建议用T{v}处理行为良好的构造，用命名的转换（比如static_cast）处理显式的类型转换。
     */
    int i = int(d);     // 截断
    std::complex z = std::complex(d);

    // int b = int(p);     // 不可移植
}
