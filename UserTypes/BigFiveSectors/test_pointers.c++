/*!
 *  \file       test_pointers.c++
 *  \brief
 *
 */


#include "pointers.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Make the unit testing for user-defined smart pointer")
{
    SECTION("If user defined the destructor, whether the generated default copy constructor and "
            "copy assignment will be disabled.")
    {
        pointers::CheckedPointer<int> handle{new int{7}};

        /*!
         *  \warning    该CheckedPointer不能使用编译器生成的拷贝构造函数。
         *              因为编译器生成的拷贝构造函数是生硬地对每个成员进行生硬的拷贝。在CheckedPointer中包含
         *              一个指针m_pointer, 若做拷贝的话，如下一行代码。 handle和copied_handle将会共用一个
         *              指针。 在析构时，handle和copied_handle两个对象就会对m_pointer删除两次。这样就会造成
         *              程序崩溃。编译器不够聪明，无法判断出来此处的错误。所以，需要程序员显式delete copy constructor
         *              and copy assignment.
         */
        // pointers::CheckedPointer<int> copied_handle{handle};

        int value = *handle;
        REQUIRE(value == 7);
    }

    SECTION("If programmer explicitly defined the copy and move operations, not adopt the compiler-generated ones.")
    {
        pointers::Handler<double> pi_handler(new double{3.1415926});

        auto copied_pi_handler = pi_handler;

        REQUIRE(*pi_handler == *copied_pi_handler);
        REQUIRE(pi_handler.get() != copied_pi_handler.get());

        pointers::Handler<double> golden_ratio_handler(new double{0.618});
        auto moved_golden_ratio_handler = std::move(golden_ratio_handler);

        REQUIRE(*moved_golden_ratio_handler == 0.618);
        REQUIRE(golden_ratio_handler.get() == nullptr);

        moved_golden_ratio_handler = std::move(pi_handler);
        REQUIRE(*moved_golden_ratio_handler == 3.1415926);
        REQUIRE(pi_handler.get() == nullptr);
    }
}