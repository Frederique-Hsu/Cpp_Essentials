/*!
 *  \file       main.cpp
 *  \brief      This file implements the main() portal for current project.
 *
 */


#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    for (int index = 0; index < argc; ++index)
    {
        std::cout << "argv[" << index << "] = " << argv[index] << std::endl;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \title      自由存储
 *
 *  \details    命名对象的生命周期是由其作用域决定的。然而，某些情况下我们希望对象与创建它的语句所在的作用域独立开来。
 *  \example    例如，很多时候我们在函数内部创建了对象，并且希望在函数返回后仍能使用这些对象。
 *              运算符new负责创建这样的对象，运算符delete则负责销毁它们。
 *              new分配的对象“位于自由存储之上”，它们存在“堆上”，或者说“在动态内存中”。
 */
