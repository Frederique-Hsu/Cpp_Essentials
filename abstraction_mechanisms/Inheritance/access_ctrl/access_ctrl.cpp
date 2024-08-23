/*!
 *  \file       access_ctrl.cpp
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

TEST(UTest4AccessCtrl, CheckDifferentAccessor)
{
    class Base
    {
    public:
        Base(int num) : bottom{num} {}
        virtual ~Base() = default;
    private:
        int bottom;
    protected:
        void changeRadius(int radius)
        {
            bottom = radius;
        }
    };

    // namespace publ
    {
        class Derived : public Base
        {
        public:
            Derived(int num, int hg) : Base(num), height{hg} {}
            ~Derived() = default;
        private:
            int height;
        protected:
        };
    }

    // namespace priv
    {
        class Derived : private Base
        {
        public:
            Derived(int num, int hg) : Base(num), height{hg} {}
            ~Derived() = default;
        private:
            int height;
        protected:
        };
    }

    // namespace prot
    {
        class Derived : protected Base
        {
        public:
            Derived(int num, int hg);
            ~Derived() = default;
        private:
            int height;
        protected:
        };
    }
}

    struct Base
    {
        int m;
        static int sm;
    };

    int Base::sm = 135;

TEST(UTest4AccessCtrl, CheckMultipleInheritanceAndAccessControl)
{
    class D1 : public virtual Base
    {
    public:
        D1(int num) : Base{.m = num}, number{num} {}
    private:
        int number;
    };

    class D2 : public virtual Base
    {
    public:
        D2(int num, double cofficient) : Base{num}, m_cofficient{cofficient} {}
    private:
        double m_cofficient;
    };

    class D12 : public D1, private D2
    {
    public:
        D12(int num, int ratio, double coff) : D1(num), D2(ratio, coff) {}
    };

    D12* pd = new D12(1, 2, 3.14);
    Base* pb = pd;

    int data = pd->m;
    EXPECT_EQ(data, 0);

    delete pd;
}

TEST(UTest4AccessCtrl, UsingDeclarationToEaseAccess)
{
    class Base
    {
    public:
        Base() : a{0}, b{0}, c{0} {}
    private:
        int a;
    protected:
        int b;
    public:
        int c;

    public:
        int geta() const { return a; }
        int getb() const { return b; }
        int getc() const { return c; }
    };

    class Derived : public Base
    {
    public:
        Derived() : Base() {}
    public:
        // using Base::a;  // error: Base::a is private, cannot access in Derived
        using Base::b;  // OK: make Base::b publicly available through Derived
    };

    /*============================================================================================*/

    Derived dobj;
    EXPECT_EQ(dobj.getb(), 0);

    dobj.b = 123;   // 使用using Base::b之后，使得Derived的对象可以public访问Base的成员。 若没有using的话，是不能public访问的。
    EXPECT_EQ(dobj.getb(), 123);

    /*============================================================================================*/

    class BB : private Base
    {
    public:
        BB() : Base() {}
    public:
        // using Base::a;      // error: a在Base中是private, BB类private继承Base，using无法授予对Base::a的访问。
        using Base::b;
        using Base::c;

        using Base::geta;   // 使用using会改变访问权限，破坏封装性。 需要考虑慎用。
        using Base::getb;
        using Base::getc;
    };

    BB bbobj;
    EXPECT_EQ(bbobj.getb(), 0);
    EXPECT_EQ(bbobj.getc(), 0);

    bbobj.b = -10;
    bbobj.c = +10;
    EXPECT_EQ(bbobj.getb(), -10);
    EXPECT_EQ(bbobj.getc(), +10);
    EXPECT_EQ(bbobj.geta(), 0);
}