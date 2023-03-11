/*!
 *  \file   Container.hpp
 *  \brief  Define an abstract type: Container
 *  
 */

#pragma once

class Container
{
public:
    virtual double& operator[](int) = 0;    /* 纯虚函数 */
    virtual int size() const = 0;           /* 常量成员函数 */
    virtual ~Container() {}                 /* 析构函数 */
};

void visit(Container& c);

class ConcreteContainer
{
public:
    ConcreteContainer();
    ~ConcreteContainer();

    double& operator[](int);
    int size() const;
};