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

GSlice::GSlice() : size{}, stride{}, dice{}
{
    std::clog << "Default constructor: GSlice::GSlice()" << std::endl;
}

GSlice::GSlice(const GSlice& rhs) : size{rhs.size}, stride{rhs.stride}, dice{rhs.dice}
{
    std::clog << "Copy constructor: GSlice::GSlice(const GSlice&)" << std::endl;
}

GSlice::GSlice(int element_count)
    : size(element_count), stride(element_count), dice(element_count)
{
    std::clog << "Ordinary constructor: GSlice::GSlice(int)" << std::endl;
}

GSlice& GSlice::operator=(const GSlice& rhs)
{
    std::clog << "Copy assignment: GSlice& GSlice::operator=(const GSlice&)" << std::endl;

    if (this != &rhs)
    {
        size = rhs.size;
        stride = rhs.stride;
        dice = rhs.dice;
    }
    return *this;
}

GSlice::GSlice(GSlice&&)
{
    std::clog << "Move constructor: GSlice::GSlice(GSlice&&)" << std::endl;
}

GSlice& GSlice::operator=(GSlice&& rhs)
{
    std::clog << "Move assignment: GSlice& GSlice::operator=(GSlice&&)" << std::endl;

    size = rhs.size;
    stride = rhs.stride;
    dice = rhs.dice;

    rhs.size.resize(0);
    rhs.stride.resize(0);
    rhs.dice.resize(0);
    return *this;
}

GSlice::~GSlice()
{
    // std::printf("\nthis pointer = %p\n", this);

    std::fprintf(stderr, "\nthis pointer = %p\n", this);
    std::clog << "Destructor: GSlice::~GSlice()\n" << std::endl;
}