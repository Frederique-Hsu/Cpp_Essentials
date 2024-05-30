/*!
 *  \file       main.cpp
 *  \brief      This project will study the lists topic in C++.
 *
 */


#include <gtest/gtest.h>


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*!
 *  \title      列表
 *
 *  \brief      我们可以用{}列表初始化命名变量，此外，在很多（但并非所有）地方{}列表还能作为表达式出现。
 *              它们的表现形式有两种：
 *  \list
 *      \li     限定为某种类型，形如T{......}，意思是“创建一个T类型的对象，并用T{......}初始化它”
 *      \li     未限定的{......}，其类型根据上下文来确定
 *  \endlist
 */


/*!
 *  \section    实现模型 Implementation model
 *
 *              {}列表的实现模型由三部分组成：
 *  \list
 *      \li     如果{}列表被用作构造函数的实参，则其实现过程与使用()列表类似。除非列表的元素以字面量传值的方式传给
 *              构造函数，否则我们不会拷贝列表的元素。
 *      \li     如果{}列表被用于初始化一个聚合体（一个数组或者一个未提供构造函数的类）的元素，则列表的每个元素分别
 *              初始化聚合体中的一个元素。除非列表的元素以传值的方式传给聚合体元素的构造函数，否则我们不会拷贝列表的元素。
 *      \li     如果{}列表被用于构建一个initializer_list对象，则列表的每个元素分别初始化initializer_list的底层
 *              数组的一个元素。通常情况下，我们把元素从initializer_list拷贝到实际使用它们的地方。
 *  \endlist
 */


/*!
 *  \section    限定列表 Qualified lists
 *
 *  \brief      把初始化器列表用作表达式的基本思想是：如果你能用下面的语句初始化一个变量x
 *
 *  \codeline   T x{v};
 *
 *  \details    那么你也能用T{v}或者new T{v}的形式创建一个对象，并将其当成一条表达式。
 *              使用限定列表构建对象与直接初始化的规则相同
 *  \note       如果某个限定列表中只包含有一个元素，则其含义基本上等同于把该元素转换成另外一种类型。
 */


/*!
 *  \section    非限定列表 Unqualified lists
 *
 *  \brief      当我们明确指导所用类型时，可以使用未限定列表。它只能被用作一条表达式，并且仅限于以下场景：
 *
 *  \list
 *      \li     函数实参
 *      \li     返回值
 *      \li     赋值运算符(=, +=, *=等)的右侧运算对象
 *      \li     下标
 *  \endlist
 */
