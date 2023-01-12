/*!
 *  \file   Vector.hpp
 *  \brief  Define a container: Vector
 *  
 */


#pragma once

class Vector
{
private:
    double *elem;   // elem指向一个包含sz个double的数组
    int sz;
public:
    Vector(int s) : elem{new double[s]}, sz{s}  // 构造函数：请求资源
    {
        for (int i = 0; i != s; ++i)
        {
            elem[i] = 0;    // 初始化元素
        }
    }
    ~Vector()   // 析构函数：释放资源
    {
        delete [] elem;
    }

    double& operator[](int i);
    int size() const;
};