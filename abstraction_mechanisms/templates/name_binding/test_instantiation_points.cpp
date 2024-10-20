/*!
 *  \file       test_instantiation_points.cpp
 *  \brief      
 *  
 */


#include "test_instantiation_points.hpp"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include <iomanip>
#include <ios>

#include <gtest/gtest.h>

namespace multiple_instantiation_points
{
    void fn(int)
    {
        std::cout << "fn(int)" << std::endl;
    }

    namespace N
    {
        class X
        {
        public:
        };

        std::string g(X obj, const std::string& str)
        {
            std::cout << "g(X, int)" << std::endl;
            return std::string(str);
        }
    }

    template<typename T, typename U>
    auto fn_temp(T t, U d)
    {
        return g(t, d);
    }

    auto x1 = fn_temp(N::X{}, "hello");

    namespace N
    {
        double g(X, double data)
        {
            std::cout << "g(X, double)" << std::endl;
            return data;
        }
    }

    auto x2 = fn_temp(N::X{}, double{2.2});

    TEST(UTest4MultipleInstantiationPoints, CheckHowToFixTemplateInstantiationAmbiguousCases)
    {
        EXPECT_TRUE(x1 == "hello");
        EXPECT_EQ(x2, 2.2);
    }
}

namespace template_and_namespace
{
    namespace N
    {
        class A
        {
        public:
        };

        char fn(A)
        {
            std::cout << "char N::fn(N::A)" << std::endl;
            return char{};
        }
    }

    char fn(int)
    {
        std::cout << "char fn(int)" << std::endl;
        return char{};
    }

    template<typename T> char g(T t)        // 此处为模板定义点
    {
        std::cout << "char g<T>(T t)" << std::endl;
        return fn(t);   // 因fn(t)是重载函数，是依赖性的，因此不能在模板定义点处绑定fn
    }

    char fn(double)
    {
        std::cout << "char fn(double)" << std::endl;
        return char{};
    }

    TEST(UTest4TemplateAndNamespace, CheckHowToInvokeOverloadedFunction)
    {
        /*!
         *  \note   编译器完成依赖性名字的绑定是通过查看以下两条来实现的：
         *  \list
         *      \li 模板定义点所处作用域中的名字
         *      \li 依赖性调用的一个实参的名字空间中的名字
         *  \endlist
         */
        char c1 = g(N::A{});        // 编译器在名字空间N中查找名为fn()的函数，最终找到了N::fn(N::A)
        char c2 = g(int{2});        // 编译器能找到fn(int)是因为它位于模板定义点的作用域中， 即在模板定义点之前
        char c3 = g(double{2.1});   // 而fn(double)不在此作用域中，即在模板定义点之后。
                                    // 实参依赖查找过程不会寻找那些只接受内置类型实参的全局函数，因此编译器找不到它。
    }
}

namespace argument_dependent_lookup     // 实参依赖查找
{
    class Customer
    {
    public:
        explicit Customer(const char* name);
    private:
        std::string m_name;
    };

    using Index = std::vector<Customer*>;

    void copy(const Index&, Index&, int deep);      // 依赖于deep的值进行深或浅拷贝

    void algo(Index& x, Index& y);

    TEST(UTest4ADL, CheckHowArgumentDependentLookupWorks)
    {
        Customer bmw("BMW"), mini{"MINI"}, rolls_royce{"Rolls Royce"};
        Index bmw_customers{&bmw, &mini, &rolls_royce};

        Index vw_customers;
        algo(bmw_customers, vw_customers);
        EXPECT_EQ(vw_customers.size(), 0);
    }

    Customer::Customer(const char* name) : m_name{name}
    {
    }

    void algo(Index& x, Index& y)
    {
        copy(x, y, static_cast<int>(false));
        // copy(x, y, false);
    }

    void copy(const Index& source, Index& target, int deep)
    {
        if (deep)
        {
            std::copy(source.begin(), source.end(), target.begin());
        }
    }
}

template<typename Range, typename Operation>
void apply(const Range& range, Operation fn)
{
    using std::begin;
    using std::end;

    for (auto& r : range)
    {
        fn(r);
    }
}


namespace template_base_class
{
    void g(int i)
    {
        std::cout << "::g(int{" << i << "})" << std::endl;
    }

    void Base::g(char c)
    {
        std::cout << "Base::g(char{" << c << "})" << std::endl;
    }

    void Base::h(char c)
    {
        std::cout << "Base::h(char{" <<  c << "})" << std::endl;
    }

    template<typename T>
    void Extension<T>::h(int i)
    {
        std::cout << "Extension<T>::h(int{" << i << "})" << std::endl;
    }

    template<typename T>
    void Extension<T>::f()
    {
        std::cout << "Extension<T>::f()" << std::endl;

        g(2);
        h(2);
    }

    TEST(UTest4TemplateBaseClass, BaseClassNotDependsOnTemplateTypeArgument)
    {
        Extension<float> ext_obj;

        ext_obj.h(5);
        ext_obj.f();
    }
/*===============================================================================================*/
    template<typename T>
    void ExT<T>::f()
    {
        std::cout << "ExT<T>::f()" << std::endl;
        g(2);
    }

    void h(ExT<Base> ext)
    {
        std::cout << "::h(ExT<Base> ext)" << std::endl;
        ext.f();
    }

    TEST(UTest4TemplateBaseClass, BaseClassDependsOnTemplateTypeArgument)
    {
        ExT<Base> ext_obj;

        ext_obj.f();

        h(ExT<Base>());
    }
}

namespace template_class_hierarchy
{
    template<typename T>
    MatrixBase<T>::MatrixBase(const std::initializer_list<T>& init_list) : sz{init_list.size()}
    {
        elements = new T[sz];
        if (elements == nullptr)
        {
            throw std::bad_alloc();
        }

        int index = 0;
        for (auto& elem : init_list)
        {
            elements[index++] = elem;
        }
    }

    template<typename T>
    MatrixBase<T>::MatrixBase(int size) : sz{size}
    {
        elements = new T[size];
        if (elements == nullptr)
        {
            throw std::bad_alloc();
        }

        for (int index = 0; index < size; ++index)
        {
            elements[index] = T{};
        }
    }

    template<typename T>
    MatrixBase<T>::~MatrixBase()
    {
        if (elements != nullptr)
        {
            delete [] elements;
        }
    }

    template<typename T>
    int MatrixBase<T>::size() const
    {
        return sz;
    }

    template<typename T, int N>
    Matrix<T, N>::Matrix(int size) : MatrixBase<T>(size), dimension{size * N}
    {
        grid[0] = MatrixBase<T>::elements;  // assign the first grid pointer with the elements from MatrixBase class.
        for (int row_index = 1; row_index < N; ++row_index)
        {
            grid[row_index] = new T[size];
        }
    }

    template<typename T, int N>
    Matrix<T, N>::~Matrix()
    {
        /*!
         *  \note   Inside the destructor, we have to start from the index=1 row to destroy the pointer array.
         *          for the index=0 pointer, let the base class MatrixBase to destruct itself.
         */
        for (int row_index = 1; row_index < N; ++row_index)
        {
            if (grid[row_index] != nullptr)
            {
                delete [] grid[row_index];
                grid[row_index] = nullptr;
            }
        }
    }

    template<typename T, int N>
    int Matrix<T, N>::size() const
    {
        return dimension;
    }

    template<typename T, int N>
    void Matrix<T, N>::assign(const std::initializer_list<T>& init_list)
    {
        auto count = init_list.size();
        int rows = count / MatrixBase<T>::sz;
        int cols = MatrixBase<T>::sz;

        int index = 0;
        for (const T& elem : init_list)
        {
            if (index >= dimension)
            {
                break;
            }
            *(grid[index / cols] + (index % cols)) = elem;
            index++;
        }
    }

    template<typename T, int N>
    T* Matrix<T, N>::data(unsigned int row_index)
    {
        if (row_index == 0)
        {
            return this->elements;
        }
        else if (row_index >= N)
        {
            return nullptr;
        }
        else
        {
            return grid[row_index];
        }
    }

    template<typename T>
    void MatrixBase<T>::print_util() const
    {
        std::cout << std::left << std::setw(8)  << " "
                  << std::right << std::setw(16) << "begin address";
        for (auto index = 1U; index <= MatrixBase<T>::size(); ++index)
        {
            /*!
             *  \attention  注意，此处需要将"column #" 与 index组合起来，因为格式化输出只能控制紧跟格式后的第一个变量，
             *              第二个变量就不受控制了。
             */
            std::cout << std::right << std::setw(16) << std::string("column #" + std::to_string(index));
        }
        std::cout << std::setw(4) << " "
                  << std::right << std::setw(16) << "end address" << std::endl;
    }

    template<typename T>
    void MatrixBase<T>::print() const
    {
        print_util();

        std::cout << std::left << std::setw(8)  << "row #1"
                  << std::right << std::setw(16) << elements;
        for (auto index = 0; index < sz; ++index)
        {
            std::cout << std::right << std::setw(16) << elements[index];
        }
        std::cout << std::setw(4) << " "
                  << std::right << std::setw(16) << (elements + sz - 1) << std::endl;
    }

    template<typename T, int N>
    void Matrix<T, N>::print() const
    {
        /*!
         *  \note   Must use this-> or MatrixBase<T>::
         *          because they are different class template, even though Matrix<T, N> inherits from MatrixBase<T>
         */
        this->print_util();
        // MatrixBase<T>::print_util();

        for (int row_index = 0; row_index < N; ++row_index)
        {
            std::cout << std::left  << std::setw(8)  << std::string("row #" + std::to_string(row_index+1));
            std::cout << std::right << std::setw(16) << grid[row_index];

            int col_index = 0;
            for (col_index = 0; col_index < MatrixBase<T>::size(); ++col_index)
            {
                std::cout << std::right << std::setw(16)
                          << std::hex << std::showbase << *(grid[row_index] + col_index);
            }

            std::cout << std::setw(4) << " "
                      << std::right << std::setw(16) << (grid[row_index] + col_index-1) << std::endl;
        }
    }

    TEST(UTest4TemplateClassHierarchy, CheckHowMatrixWasInstantiated)
    {
        Matrix<int, 4> matrix(5);   // 4 row * 5 col

        matrix.assign({10, 20, 30, 40, 50, 60, 70, 80, 90});
        matrix.print();
        // matrix.MatrixBase<int>::print();

        EXPECT_EQ(matrix.size(), 4 * 5);
        EXPECT_EQ(matrix.MatrixBase<int>::size(), 5);

        int* elements = matrix.data(1);
        EXPECT_EQ(elements[0], 60);
        EXPECT_EQ(elements[1], 70);
        EXPECT_EQ(elements[2], 80);
        EXPECT_EQ(elements[3], 90);
        EXPECT_EQ(elements[4],  0);

        elements = matrix.data(0);
        EXPECT_EQ(elements[0], 10);
        EXPECT_EQ(elements[1], 20);
        EXPECT_EQ(elements[2], 30);
        EXPECT_EQ(elements[3], 40);
        EXPECT_EQ(elements[4], 50);

        elements = matrix.data(5);
        EXPECT_EQ(elements, nullptr);
    }
}
