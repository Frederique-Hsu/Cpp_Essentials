/*!
 *  \file       big_five_sectors.hpp
 *  \brief
 *
 */


#pragma once

#include <string>

/*!
 *  \section    Definitions
 */


/*!
 *  \class      X
 *  \details    一个类型的构造函数、析构函数以及拷贝、赋值与移动操作在逻辑上不是相互独立的。
 *              我们定义的这组函数必须相互匹配，否则就会引起逻辑问题或性能问题。
 *              如果一个类X的析构函数执行很重要的任务，如释放自由存储空间或释放锁，那么这个类
 *              就需要一组完整的函数。
 */
class X
{
public:
    X(const std::string& str);      // "ordinary constructor": create an object
    X();                            // default constructor
    X(const X& rhs);                // copy constructor
    X(X&& rhs);                     // move constructor
    X& operator=(const X& rhs);     // copy assignment: clean up target and copy
    X& operator=(X&& rhs);          // move assignment: clean up target and move
    ~X();                           // destructor: clean up
};

/*================================================================================================*/

class Vector
{
public:
    explicit Vector(int size);
    ~Vector();

private:
    double* elem;   // elem指向一个数组，保存sz个double元素
    int sz;         // sz非负

public:
    class BadSize
    {
    public:
        BadSize(int size);
    };
};

/*!
 *  \note   构造函数会“自顶向下”地创建一个类对象：
 *  \list
 *      \li [1] 首先，构造函数调用其基类的构造函数
 *      \li [2] 然后，它调用成员的构造函数。当有多个成员时，按照从上到下的先后顺序依次进行构造。
 *      \li [3] 最后，它执行自身的函数体
 *  \endlist
 *
 *  \note   析构函数则按相反顺序“销毁”一个对象：
 *  \list
 *      \li [1] 首先，析构函数执行自身的函数体
 *      \li [2] 然后，它调用其成员的析构函数。当有多个成员时，按照从下往上的先后顺序依次进行析构。
 *      \li [3] 最后，它调用其基类的析构函数
 *  \endlist
 */

class Shape
{
public:
    virtual void draw() = 0;

    virtual ~Shape();
};

class Circle : public Shape
{
public:
    void draw();

    ~Circle();
};

/*================================================================================================*/
