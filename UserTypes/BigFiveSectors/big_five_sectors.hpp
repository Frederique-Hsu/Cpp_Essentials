/*!
 *  \file       big_five_sectors.hpp
 *  \brief
 *
 */


#pragma once

#include <string>
#include <valarray>
#include <vector>

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

class GSlice
{
    std::valarray<std::size_t> size;
    std::valarray<std::size_t> stride;
    std::valarray<std::size_t> dice;

public:
    GSlice();
    ~GSlice();
    explicit GSlice(int element_count);
    GSlice(const GSlice&);
    GSlice(GSlice&&);
    GSlice& operator=(const GSlice&);
    GSlice& operator=(GSlice&&);
};


class TicTacToe
{
public:
    enum class State
    {
        empty,
        nought,
        cross
    };

public:
    TicTacToe() = default;
    TicTacToe(const TicTacToe&) = default;
    TicTacToe& operator=(const TicTacToe&) = default;
    ~TicTacToe() = default;
    
private:
    std::vector<State> pos{std::vector<State>(9)};
};

/*!
 *  \note       对于每一个类，我们都应该问：
 *  \list
 *      \li     需要默认构造函数吗？ （由于默认构造函数不能满足要求或已被另一个构造函数所禁止）
 *      \li     需要析构函数吗？ （例如，由于某些资源需要释放）
 *      \li     需要拷贝操作吗？ (由于默认拷贝语义不能满足需求，例如，由于类是一个基类，或它包含指针，指向的对象必须被释放。)
 *      \li     需要移动操作吗？ (由于默认语义不能满足需求，例如，由于空对象无意义。)
 *  \endlist
 */

class Base
{
public:
    Base() = default;
    ~Base() = default;

    /*!
     *  \attention  我们可以“删除”一个函数：即，可以声明一个函数不存在，从而令（隐式或显式）使用它的尝试成为错误。
     *              这种机制最明显的应用是消除其他默认函数。例如，防止拷贝基类很常见的，因为这种拷贝容易导致切片。
     */
    Base(const Base&) = delete;
    Base& operator=(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(Base&&) = delete;
};


template<class T> T* clone(T* ptr)
{
    return new T{*ptr};
}

class Foo
{
};

/*!
 *  \note   可以使用delete删除任何我们能声明的函数。
 *          例如，我们可以将一个特例化版本从函数模板的众多可能的特例化版本中删除。
 */
Foo* clone(Foo*) = delete;      // 不要尝试克隆一个Foo