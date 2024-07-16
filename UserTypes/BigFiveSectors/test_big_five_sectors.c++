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
