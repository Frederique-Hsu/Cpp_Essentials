/*!
 *  \file       test_copy.c++
 *  \brief      
 *  
 */


#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <iostream>

TEST_CASE("Copy the base classes")
{
    struct Father
    {
        Father() {}
        Father(const Father&) {}
    };

    struct Mother
    {
        Mother(int) {}
        Mother(const Mother&) {}
    };

    SECTION("Check the derived class how to implement the copy constructor")
    {
        struct Son : Father, Mother
        {
            Son(int i) : Father{}, Mother{i}, fobj{}, mobj{2 * i}
            {
            }
            Son(const Son& rhs) : Father{rhs}, Mother{rhs}, fobj{rhs.fobj}, mobj{rhs.mobj}
            {
            }

            Father fobj;
            Mother mobj;
        };
    }

    SECTION("Check whether the default copy constructor will copy the pointer")
    {
        struct S
        {
            int* p;
        };

        S obj{new int{5}};

        auto fn = [&obj]() {
            S instance{obj};    // copy the obj

            *instance.p = 1;    // change the instance, but it affect the obj.
            REQUIRE(*obj.p == 1);
            
            *obj.p = 2;         // changed the obj, whereas it affect the instance reflectly.
            REQUIRE(*instance.p == 2);

            delete instance.p;  // affect both instance and obj

            instance.p = new int{3};
            REQUIRE(*instance.p == 3);
            REQUIRE(*obj.p == 3);

            *obj.p = 4;
            REQUIRE(*instance.p == 4);
        };

        fn();
        delete obj.p;
    }

    SECTION("对于与共享子对象生命周期相关的问题，我们可以通过引入某种形式的垃圾收集机制来解决")
    {
        struct S
        {
            std::shared_ptr<int> p;
        };

        S xobj{std::shared_ptr<int>(new int{124})};
        REQUIRE(*xobj.p == 124);

        auto fn = [xobj]() {
            S yobj{xobj};           // yobj copied from xobj

            *yobj.p = 1;            // changed the yobj, meanwhile it affected the xobj
            REQUIRE(*xobj.p == 1);

            *xobj.p = 2;            // changed the xobj, but it affected the yobj
            REQUIRE(*yobj.p == 2);

            yobj.p.reset(new int{18});  // although changed the yobj, but it did not affect the xobj
            REQUIRE(*xobj.p == 2);

            *xobj.p = 25;               // xobj had changed, but it did not shared with yobj, so the yobj keep the previous value
            REQUIRE(*yobj.p == 18);
        };

        fn();
    }
}

SCENARIO("Research on the shallow copy and deep copy, prevent the slicing issue between base and derived classes")
{
    std::cout << "\n" << std::endl;
    /*!
     *  \note   一个指向派生类的指针可隐式转换为指向其公有基类的指针。
     *          当这一简单且必要的规则应用于拷贝操作时，就会导致一个容易让人中招的陷阱。即：切片问题 slicing
     */
    GIVEN("Define the base and derived classes")
    {
        struct Base
        {
            int bnumber;

            Base(int num = 0) : bnumber{num}
            {
                std::cout << "called the Base::base()" << std::endl;
            }
            Base(const Base&)
            {
                std::cout << "called the Base::Base(const Base&)" << std::endl;
            }
            Base& operator=(const Base&) = delete;
        };

        struct Derived : Base
        {
            int dnumber;

            Derived(int num = 0) : Base(num), dnumber{num}
            {
                std::cout << "called the Derived::Derived()" << std::endl;
            }
            Derived(const Derived& rhs) : Base{rhs}
            {
                std::cout << "called the Derived::Derived(const Derived&)" << std::endl;
            }
            Derived& operator=(const Derived&) = delete;
        };

        WHEN("copy the object from the base class")
        {
            auto naive = [](Base* ptr) {
                Base bobj = *ptr;   // copy to the object from Base, it may incur the slicing issue
            };

            THEN("the slicing issue will break out")
            {
                Derived dobj;
                naive(&dobj);

                /*!
                 *  \warning    下面一行代码，从Derived对象拷贝到Base对象，就发生了切片问题。
                 *              本应该调用Derived::Derived(const Derived&)的，却调用了Base::Base(const Base&)
                 */
                Base bobject = dobj;
                /*!
                 *  \details    dobj包含了Base部分的副本，即dobj.bnumber的副本。
                 *              dobj向bobject拷贝时，dobj.dnumber并不会被拷贝，这种现象称为切片 slicing
                 * 
                 *              这可能正是你所期望的，但这通常是一个微妙的错误。 如果你不希望发生切片，可以采取以下方法防止这种现象：
                 *  \list
                 *      \li     禁止拷贝基类：delete拷贝操作
                 *      \li     防止派生类指针转化为基类指针：将基类声明为private或protected基类
                 *  \endlist
                 */
                std::cout << "\n" << std::endl;
            }
        }
    }
}