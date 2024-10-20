/*!
 *  \file       test_instantiation_points.hpp
 *  \brief      
 *  
 */


#pragma once

#include <initializer_list>

class Quad
{
public:
};


namespace template_base_class
{
    void g(int);

    class Base
    {
    public:
        void g(char);
        void h(char);
    };

    template<typename T>
    class Extension : public Base   // 基类不依赖于模板实参
    {
    public:
        void h(int);
        void f();
    };

    template<typename T>
    class ExT : public T    // 基类依赖于模板实参
    {
    public:
        void f();
    };

    void h(ExT<Base> ext);
}

namespace template_class_hierarchy
{
    template<typename T> class MatrixBase
    {
    public:
        explicit MatrixBase(int size);
        MatrixBase(const std::initializer_list<T>& init_list);
        virtual ~MatrixBase();
    protected:
        int sz;
        T* elements;
    public:
        virtual int size() const;
        virtual void print() const;
    protected:
        void print_util() const;
    };

    template<typename T, int N> class Matrix : public MatrixBase<T>     // N-dimensional matrix
    {
    public:
        Matrix(int size);
        ~Matrix();
    private:
        int dimension;
        T* grid[N];
    public:
        void assign(const std::initializer_list<T>& init_list);
        T* data(unsigned int row_index);
        virtual int size() const override;
        virtual void print() const override;
    };
}
