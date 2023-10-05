/*!
 *  \file       lambda_expressions.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>
#include <iostream>

/*!
 *  \note       lambda expression
 *
 *  \note       lambda表达式是定义和使用匿名函数对象的一种简便的方式。
 *              人们习惯的传统方式是先定义一个含有operator()的命名类，随后再创建类的一个对象，并通过该对象调用函数。
 *
 *  \list
 *  \li         一条lambda表达式包含以下组成要件：
 *
 *  \li         1. 一个可能为空的捕获列表(capture list)，指明定义环境中的哪些名字能被用在lambda表达式内，
 *                 以及这些名字的访问方式是拷贝还是引用。捕获列表位于[]内
 *
 *  \li         2. 一个可选的参数列表 (parameter list)，指明lambda表达式所需的参数。参数列表位于()内。
 *
 *  \li         3. 一个可选的mutable修饰符，指明该lambda表达式可能会修改它自身的状态（即，改变通过值捕获的变量的副本）。
 *
 *  \li         4. 一个可选的->形式的返回声明
 *
 *  \li         5. 一个可选的noexcept修饰符
 *
 *  \li         6. 一个表达式体(body)，指明要执行的代码，表达式体位于{}内
 *  \endlink
 *
 *  \warning    在lambda的概念中，传参、返回结果以及定义表达式体等环节都与函数的相应概念是一致的。
 *              区别在于函数没有提供局部变量“捕获”的功能，这意味着lambda可以作为局部函数使用，
 *              而普通函数不能。
 */


void print_modulo(const std::vector<int>& v, std::ostream& os, int m);

class Modulo_print
{
    std::ostream& os;
    int m;
public:
    Modulo_print(std::ostream& os, int m);
    void operator()(int x) const;
};

#define DFS_Traversal       1
#define BFS_Traversal       2
#define Traversal           DFS_Traversal

template<class Container>
void print_modulo(const Container& container, std::ostream& os, int m)
{
#if (Traversal == DFS_Traversal)
    std::cout << "Calling the edition of generic function template:" << std::endl;
    for (auto& elem : container)
    {
        if (elem % m == 0)
        {
            os << elem << std::endl;
        }
    }
#elif (Traversal == BFS_Traversal)
    std::breadth_first(std::begin(container),
                       std::end(container),
                       [&os, m](int x)
                       {
                           if (x % m == 0)
                           {
                               os << x << std::endl;
                           }
                       });
#endif
}

void algo(std::vector<int>& vec);
void algo(std::vector<int>& vec, bool sensitive);

template<typename... Var> auto help1 = [](Var... vargs){
    std::cout << "Calling help1(vargs...)" << std::endl;
};

template<typename... Var> auto help2 = [](Var... vargs){
    std::cout << "Calling help2(vargs...)" << std::endl;
};

template<typename... Var> void algo(int s, Var... v)
{
    auto helper = [s, &v...] {
        return s * (help1<Var...>(v...) + help2<Var...>(v...));
    };
}
