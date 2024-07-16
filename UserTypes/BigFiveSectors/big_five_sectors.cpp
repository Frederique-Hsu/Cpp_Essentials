/*!
 *  \file       big_five_sectors.cpp
 *  \brief
 *
 */


#include "big_five_sectors.hpp"

#include <iostream>

/*!
 *  \section    Implementations
 */

X::X(const std::string&)
{
}

X::X()
{
}

X::X(const X&)
{
}

X::X(X&&)
{
}

X& X::operator=(const X&)
{
    return *this;
}

X& X::operator=(X&&)
{
    return *this;
}

/*================================================================================================*/

/*!
 *  \note   构造函数的任务是初始化该类的一个对象。一般而言，初始化操作必须建立一个
 *          类不变式(class invariant). 所谓不变式就是当成员函数（从类外）被调用时必须保持的某些东西。
 */
Vector::Vector(int size)
{
    if (size < 0)
    {
        throw BadSize(size);
    }

    sz = size;
    elem = new double[size];

#if defined(DEBUG)
    std::cout << "called the Vector(int size = " << size << ") constructor." << std::endl;
#endif
}

Vector::BadSize::BadSize(int size)
{
#if defined(DEBUG)
    std::cout << "The size = " <<  size << " is negative." << std::endl;
#endif
}

/*!
 *  \attention  这种基于构造函数/析构函数的资源管理风格被称为
 *              “资源获取即初始化” (Resource Acquisition Is Initialization, RAII)
 */
Vector::~Vector()
{
    delete [] elem;

#if defined(DEBUG)
    std::cout << "called the ~Vector() destructor." << std::endl;
    std::cout << sz << " elements had been freed." << std::endl;
#endif
}


Shape::~Shape()
{
    std::cout << "called the base class Shape::~Shape()" << std::endl;
}

void Circle::draw()
{
    std::cout << "called the derived class Circle::draw()" << std::endl;
}

Circle::~Circle()
{
    std::cout << "called the derived class Circle::~Circle()" << std::endl;
}
