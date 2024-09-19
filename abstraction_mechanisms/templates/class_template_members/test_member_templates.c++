/*!
 *  \file       test_member_templates.c++
 *  \brief      
 *  
 */


#include "member_templates.hpp"
#include "list.hpp"
#include "allocator.hpp"

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>


TEST(UTest4MemberTemplates, CheckComplexConstruction)
{
    Complex<int> empty_comp;
    EXPECT_EQ(empty_comp.real(), int{});
    EXPECT_EQ(empty_comp.imag(), int{});
    
    Complex<long> comp(3, 4);
    EXPECT_EQ(comp.real(), 3);
    EXPECT_EQ(comp.imag(), 4);
}

TEST(UTest4MemberTemplates, CheckComplexTypeConversion)
{
    Complex<float> cf;
    Complex<double> cd{cf};
    // Complex<float> cf2(cd);     // Error: narrowing conversion in m_real{rhs.real()} from 'double' to 'float'
    
    // Complex<float> cf3(2.0, 3.0);   // Error: 因为2.0, 3.0默认是double类型，double向float转换会窄化
    Complex<double> cd2(2.0F, 3.0F);    // OK: float向double转化完全正确，无窄化问题。
    
    class Quad
    {
    };
    
    Complex<Quad> cq;
    // Complex<int> ci(cq);    // Error: 不存在Quad向int的转换
}

    template<typename T> class MyAllocator
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = T*;
    };
        
    template<typename T> class YourAllocator
    {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        
    };
    
    #if false
    void user(List<int, MyAllocator<int>>& my_list, List<int, YourAllocator<int>>& your_list)
    {
        [[maybe_unused]] auto p = std::find(my_list.begin(), my_list.end(), 17);
        [[maybe_unused]] auto q = std::find(your_list.begin(), your_list.end(), 20);
    }
    #endif
    
TEST(UTest4MemberTemplates, UtilizeNestedTypeDefinitionInsideClassTemplate)
{
    
    List<double, MyAllocator<double>> my_list;
    List<double, YourAllocator<double>> your_list;
}

TEST(UTest4Allocator, CheckUserDefinedSimpleAllocator)
{
    SimpleAllocator<int> alloc;
    std::vector<int, SimpleAllocator<int>> numbers(alloc);
    
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    
    for (auto number : numbers)
    {
        std::cout << number << ",  ";
    }
    std::cout << std::endl;
    EXPECT_EQ(numbers.size(), 5);
}

namespace my
{
    template<typename T> class Matrix;
    template<typename T> class Vector;
    
    template<typename T> class Vector
    {
        T v[4];
    public:
        friend Vector<T> operator*(const Matrix<T>&, const Vector&)
        {
            return Vector<T>();
        }
    };
    
    template<typename T> class Matrix
    {
        Vector<T> v[4];
    public:
        friend Vector<T> operator*(const Matrix&, const Vector<T>&)
        {
            return Vector<T>();
        }
    };
    
    template<typename T> Vector<T> operator*(const Matrix<T>& matrix, const Vector<T>& vector)
    {
        Vector<T> result;
        /*!
         *  \todo   to be implemented here
         */
        return result;
    }
}


namespace {    
    class C;
    using C2 = C;
    
    template<typename T>
    class MyClass
    {
        friend C;
        friend C2;
        // friend C3;      // error: 在作用域中不存在一个类名为C3
        friend class C4;
    };   
    
    template<typename T>
    class MyOtherClass
    {
        friend T;
        friend MyClass<T>;
        // friend class T;     // error: 'class' 是多余的
    };
    
    template<typename T, typename Allocator> class MyList;
    
    template<typename T> class MyLink
    {
        template<typename U, typename Allocator> friend class MyList;
    };
    
    TEST(UTest4Friend, CheckClassTemplateFriend)
    {
    }
}