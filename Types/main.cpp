/*!
 *  \file       main.cpp
 *  \brief      研究C++的各种数据类型
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \note       命名风格
 *
 *  \remark     程序员最好遵循某些约定俗成的命名风格，并且坚持下去，不要轻易改变。
 *
 *  \list
 *              1. 用户自定义类型名的首字母大写， 如Shape
 *              2. 非类型实体名的首字母小写， 如 current_token
 *              3. 在宏定义中全部使用大写字母，前提是当你不得不使用宏时， 如HACK.
 *                 在其他场合绝对不要这样做，即使非宏常量也不行。
 *              4. 用下划线把标识符中的单词隔开， 如number_of_elements比numberOfElements的可读性更好
 *  \endlist
 *
 *  \warning    请注意，C++语言和标准库中的类型名字都是小写，有时候这条线索可以帮助我们判断某个类型名字是否来源于C++标准
 */
