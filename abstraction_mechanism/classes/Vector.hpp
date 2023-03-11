/*!
 *  \file   Vector.hpp
 *  \brief  Define a container: Vector
 *  
 */


#pragma once

#include <initializer_list>
#include <stdexcept>

class Vector
{
private:
    double *elem;   // elem指向一个包含sz个double的数组
    int sz;
public:
    Vector(int s) : elem{new double[s]}, sz{s}  // 构造函数：请求资源
    {
        if (s < 0)
        {
            throw std::length_error("length of a vector is negative");
        }
        for (int i = 0; i != s; ++i)
        {
            elem[i] = 0;    // 初始化元素
        }
    }
    Vector(std::initializer_list<double>);  /* 使用一个列表进行初始化 */
    ~Vector()   // 析构函数：释放资源
    {
        delete [] elem;
    }

    double& operator[](int i);
    int size() const;
    void push_back(double);     /* 在末尾添加一个元素，容器的长度加1 */
};