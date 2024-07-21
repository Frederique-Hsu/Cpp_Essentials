/*!
 *  \file       test_big_five_sectors.c++
 *  \brief
 *
 */


#include "big_five_sectors.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>

static Vector* f(int sz)
{
    Vector v1(sz);

    return new Vector(sz + sz);
}

static void g(int size)
{
    Vector* p = f(size);

    delete p;
}

TEST_CASE("Check the class invariant, and its constructor and destructor", "[Vector]")
{
    SECTION("Observe whether the allocated memory had been freed?")
    {
        g(5);
    }

    SECTION("If invoking Vector(int size = -2) failed, observe whether to throw an exception?")
    {
        REQUIRE_THROWS_AS(Vector(-2), Vector::BadSize);
    }
}

TEST_CASE("Inspect the construction order", "[constructor]")
{
    struct S1
    {
        std::string s;
    };

    SECTION("If no constructor was provided by user, check whether compiler will provide one?")
    {
        S1 x;

        REQUIRE(x.s == "");
    }

    struct X
    {
    private:
        int m_num;
    public:
        X(int number) : m_num(number)
        {
            std::cout << "called the constructor X(int)" << std::endl;
        }

        int number() const
        {
            return m_num;
        }
    };

    struct S2
    {
        X x;
    };

    SECTION("Check the constructor invokation by what order")
    {
        // S2 obj1;    // Error: 没有为obj1.x提供初始值
        S2 obj2{3};     // OK: obj2.x用3进行了初始化

        REQUIRE(obj2.x.number() == 3);
    }
}

SCENARIO("Define a special class, whether we can prevent it from destroying?")
{
    GIVEN("Define a Nonlocal class")
    {
        class NonLocal
        {
        public:
            NonLocal()
            {
                std::cout << "Called the NonLocal() constructor." << std::endl;
            }

            void destroy()
            {
                std::cout << "By explicitly calling the destructor..." << std::endl;
                this->~NonLocal();
            }

        private:
            ~NonLocal()
            {
                std::cout << "Cannot implicitly destructing." << std::endl;
            }
        };

        WHEN("Define the object of NonLocal class")
        {
            // NonLocal obj;   // Error: 不能析构一个NonLocal

            NonLocal* ptr = new NonLocal;

            // delete ptr;     // Error: 不能析构一个NonLocal

            ptr->destroy();
        }
    }
}

TEST_CASE("Check the virtual destructor", "[virtual destructor]")
{
    auto user = [](Shape* ptr) -> void {
        ptr->draw();
        // do something else ...
        delete ptr;
    };

    SECTION("Why need to have the destrictor been virtual?")
    {
        Shape* pobj = new Circle();

        /*!
         *  \warning    如果父类Shape没有使用virtual destructor，会发现delete ptr时没有调用
         *              子类Circle的析构函数。证明子类发生了内存泄漏。
         *              所以，对于抽象类的析构函数必须为virtual。
         */
        user(pobj);
    }
}

TEST_CASE("Check which is calling the Big-Five-Sectors of a class respectively")
{
    auto call = [](const GSlice& arg)
    {
        GSlice gs0;                     // Default constructor
        std::fprintf(stderr, "&gs0 = %p\n\n", &gs0);

        GSlice gs1(gs0);                // Copy constructor
        std::fprintf(stderr, "&gs1 = %p\n\n", &gs1);

        GSlice gs2 = arg;               // Copy constructor
        std::fprintf(stderr, "&gs2 = %p\n\n", &gs2);

        gs2 = gs0;                      // Copy assignment
        std::fprintf(stderr, "&gs2 = %p\n\n", &gs2);

        GSlice robj = std::move(gs0);   // Move constructor
        std::fprintf(stderr, "&robj = %p\n\n", &robj);

        robj = std::move(gs1);          // Move assignment
        std::fprintf(stderr, "&obj = %p\n\n", &robj);

        return robj;
    };

    SECTION("Invoke the previous lambda function to see their logs")
    {
        GSlice obj(5);                  // Ordinary constructor
        std::fprintf(stderr, "&obj = %p\n\n", &obj);

        auto result = call(obj);
        std::fprintf(stderr, "&result = %p\r\n", &result);
    }
}

TEST_CASE("Deleting the function can prevent from calling it", "[delete]")
{
    auto fn = [](Circle* pc, Foo* pf) {
        Circle* pc2 = clone(pc);
        // Foo* pf2 = clone(pf);   // Error: clone(Foo*)已被删除，不能调用

        delete pc2;
    };

    struct Z
    {
        Z(double d) : elem{d} {}
        Z(int) = delete;
        
    private:
        double elem;
    };

    SECTION("Check how the deleted constructor can prevent from calling them")
    {
        // Z zint{5};       // Error: Z(int) constructor had been remarked "=delete"
        Z zdouble{1.0};
    }

    /*!
     *  \attention  delete的进一步用途是控制在哪里分配类对象
     */
    class NotOnStack
    {
    public:
        ~NotOnStack() = delete;
    };

    class NotOnFreeStore
    {
    public:
        void* operator new(std::size_t) = delete;
    };

    SECTION("Deleting destructor and new operator can control where to allocate for objects")
    {
        // NotOnStack v1;      // Error: 该对象v1不能在栈空间被销毁
        NotOnFreeStore v2;  // OK

        NotOnStack* p1 = new NotOnStack;        // OK
        // NotOnFreeStore* p2 = new NotOnFreeStore;    // Error: 不能在自由堆空间为指针对象p2分配内存。

        // delete p1;      // 但这样也永远不能使用delete删除NotOnStack对象p1了。
    }
}