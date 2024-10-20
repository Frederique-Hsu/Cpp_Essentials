/*!
 *  \file       Test_Inheritance.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>


TEST(UTest4Inhertance, CheckOverrideConstrollingInDeeperClassHierarchy)
{
    struct B0
    {
        void f(int) const 
        {
            std::cout << "Called B0::f(int) const" << std::endl;
        }
        virtual void g(double) 
        {
            std::cout << "Called B0::g(double)" << std::endl;
        }
    };

    struct B1 : B0 { /* ... */ };
    struct B2 : B1 { /* ... */ };
    struct B3 : B2 { /* ... */ };
    struct B4 : B3 { /* ... */ };
    struct B5 : B4 { /* ... */ };

    struct D : B5
    {
        void f(int) const   /*! \warning    not override, but hide the B0::f(int), because B0::f(int) is not virtual */
        // void f(int) const override      // error: B0:f(int) is not virtual
        {
            std::cout << "Called D::f(int) const" << std::endl;
        }
        void g(int)        /*! \attention  D::g(int) hide B0::g(double) */
        // void g(int) override    // error: B0::g(double) takes a double argument
        {
            std::cout << "Called D::g(int)" << std::endl;
        }
        virtual int h()     /*! \attention  D::h() is a new virtual function */
        // virtual int h() override    // error: no function h() to override
        {
            std::cout << "Called D::h()" << std::endl;
            return int{};
        }
    };

    /*!
     *  \note   对于大型类层次，需要用到特性的覆盖控制机制
     *  \list
     *      \li     virtual: 函数可能被覆盖
     *      \li     = 0: 函数必须是virtualde的，且必须被覆盖。
     *      \li     override: 函数要覆盖基类中的一个虚函数
     *      \li     final: 函数不能被覆盖
     *  \endlist
     * 
     *          如果不使用个这些覆盖控制，一个非static成员函数为虚函数当且仅当它覆盖了基类中的一个virtual函数。
     */
}

TEST(UTest4Inheritance, PreventMoreOverrideOrInherit)
{
    struct Node
    {
        using Type = int;
        virtual Type type() = 0;
    };

    class If_Statement : public Node
    {
    public:
        Type type() override final      // prevent further overriding
        {
            return Type{};
        }
    };

    class Modified_If_Statement : public If_Statement
    {
    public:
        #if false
        Type type() override    // error: If_Statement::type() is final
        {
            return Type{};
        }
        #endif
    };

    class For_Statement final : public Node
    {
    public:
        Type type() override { return Type{}; }
    };

    #if false
    class Modified_For_Statement : public For_Statement     // error: 不能将"final"类作为基类
    {
    public:
        Type type() override;
    };
    #endif
}

TEST(UTest4Inheritance, FunctionOverloadingCannotSpanAcrossScopes)
{
    struct Base
    {
        void f(int)
        {
            std::cout << "Called Base::f(int)" << std::endl;
        }
    };

    struct Derived : Base
    {
        void f(double)
        {
            std::cout << "Called Derived::f(double)" << std::endl;
        }
    };

    auto use = [](Derived d)
    {
        d.f(1);

        Base& br = d;
        br.f(2);
    };
    Derived myd;
    use(myd);

    std::cout << "===============================================================================" << std::endl;

    /*!
     *  \note   我们有时希望函数重载能够保证选择最佳匹配的成员函数。
     *          类似于名字空间，我们可以使用using声明将一个函数加入作用域中。
     */
    struct D2 : Base
    {
        using Base::f;      // 将Base中的所有f加入到D2

        void f(double)
        {
            std::cout << "Called D2::f(double)" << std::endl;
        }
    };

    auto use2 = [](D2 d)
    {
        d.f(1);

        Base& br = d;
        br.f(2);
    };
    D2 d2obj;
    use2(d2obj);
}

TEST(UTest4Inheritance, UseDeclarationToIntroduceMultipleBaseClasses)
{
    struct B1
    {
        void f(int) { std::cout << "Called B1::f(int)" << std::endl; }
    };
    
    struct B2
    {
        void f(double) { std::cout << "Called B2::f(double)" << std::endl; }
    };

    struct D : B1, B2
    {
        using B1::f;
        using B2::f;

        void f(char) { std::cout << "Called D::f(char)" << std::endl; }
    };

    auto use = [](D obj)
    {
        obj.f(1);
        obj.f('a');
        obj.f(1.0f);
    };

    D dobj;
    use(dobj);
}