/*!
 *  \file       test_function_template_overloading.c++
 *  \brief      
 *  
 */


#include "function_template_overloading.hpp"

#include <cmath>
#include <bitset>
#include <typeindex>
#include <gtest/gtest.h>


TEST(UTest4FnTemplateOverloading, CheckOverloadedSqrtFunction)
{
    double number = 4.0;
    auto result = sqrt(number);
    
    EXPECT_EQ(typeid(result), typeid(double));
    EXPECT_DOUBLE_EQ(result, 2.0);
    
    std::complex<double> z{3.0, 4.0};
    // auto complex_result = sqrt(z);     // Error: call of overloaded 'sqrt<int>(std::complex<int>)' is ambiguous
}

namespace parsing_rule_for_function_template_overloading
{
    using std::type_index;
    using std::string;
    
    class A
    {
    public:
        virtual ~A() = default;
    };
    class B : public A {};
    class C : public A {};
    
    std::unordered_map<type_index, string> type_names{
        {type_index(typeid(int)),       "int"},
        {type_index(typeid(double)),    "double"},
        {type_index(typeid(float)),     "float"},
        {type_index(typeid(char)),      "char"},
        {type_index(typeid(A)),         "A"},
        {type_index(typeid(B)),         "B"},
        {type_index(typeid(C)),         "C"}
    };
    
    template<typename T>
    T max(T t1, T t2)
    {
        std::cout << "T max<T>(T, T) is " << type_names[type_index(typeid(T))] << std::endl;
        
        if (t1 >= t2)
            return t1;
        else // if (t1 < t2)
            return t2;
    }

    /*!
    *  \attention  通过添加适当的声明来消解二义性
    */
    template<typename T>
    T min(T t1, T t2)
    {
        std::cout << "T min<T>(T, T) is " << type_names[type_index(typeid(T))] << std::endl;
        
        if (t1 <= t2)
            return t1;
        else    // if (t1 > t2)
            return t2;
    }
    // 对于以下这些普通函数，编译器优先选用，应用普通重载规则，而且使用inline确保没有额外开销。
    inline int    min(int i, int j)             { return min<int>(i, j); }
    inline double min(int i, double d)          { return min<double>(i, d); }
    inline double min(double d, int i)          { return min<double>(d, i); }
    inline double min(double d1, double d2)     { return min<double>(d1, d2); }

    TEST(UTest4FnTemplateOverloading, CheckOverloadParsingRule)
    {
        const int s = 7;
        
        auto fn = []()
        {
            max(1, 2);          // 匹配 max<int>(1, 2)
            max('a', 'b');      // 匹配 max<char>('a', 'b')
            max(2.7, 4.9);      // 匹配 max<double>(2.7, 4.9)
            // max(2.7F, 4.9);     // 不匹配， 因为 max((float)2.7F, (double)4.9)， 两个类型不一致。因为函数模板实参是通过模板实参推断确定的，
                                // 则不能对它进行提升、标准类型转换或用户自定义类型转换
            max(s, 7);          // max<int>(int{s}, 7), 使用了简单的类型转换
            
            // max('a', 1);        // 错误， 有二义性，到底是 max<char, char>() 还是 max<int, int>() ?
            // max(2.7, 4);        // 错误， 有二义性， max<double, double>() 还是 max<int, int>() ?
            
            // 但可以通过显式限定来消解二义性    
            max<int>('a', 1);           // max<int>(int('a'), 1)
            max<double>(2.7, 4);        // max<double>(2.7, double(4))
        };
        fn();
        std::cout << "\n" << std::endl;
        auto gc = []()
        {
            min(1, 2);
            min('a', 'b');
            min(2.7, 4.9);
            min(2.7F, 4.9);
            min('a', 1);
            min(2.7, 4);
        };
        gc();
    }
}

TEST(UTest4FnTemplateOverloading, CheckArgumentSubstitutionFailure)
{
    auto fn = [](std::vector<int>& v, int* p, int n, auto& x, auto& y)
    {
        x = mean(v.begin(), v.end());
        y = mean(p, p + n);
    };
    
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array[10] =     {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    int x = 0, y = 0;
    fn(vec, array, sizeof(array)/sizeof(int), x, y);
    EXPECT_EQ(x, y);
}

TEST(UTest4FnTemplateOverloading, CheckHowTemplateParsingRuleAppliedOnInheritanceMechanism)
{
#define USE_LAMBA_EXPRESSION_OBJECT

#if defined (USE_LAMBA_EXPRESSION_OBJECT)
    auto checkLeapYear = [](volatile int year)
    {
        if ((year % 4 == 0 and year % 100 != 0) or (year % 400 == 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    };
#endif
    
    auto fn = [](Base<int>* pbase, bool& result)
    {
        result = execute(pbase);
    };
    
    Base<int> base(2023);
#if defined (USE_LAMBA_EXPRESSION_OBJECT)
    Derived<int> derived(2024, checkLeapYear);
#else
    Derived<int> derived(2024, 
                         [](const int year) -> bool
                         {
                            if ((year % 4 == 0 and year % 100 != 0) or (year % 400 == 0))
                            {
                                return true;
                            }
                            else
                            {
                                return false;
                            }
                         });
#endif
    
    bool is_leap_year;
    fn(&base, is_leap_year);
    EXPECT_EQ(is_leap_year, bool{});
    
    fn(&derived, is_leap_year);
    EXPECT_EQ(is_leap_year, true);
}

TEST(UTest4FnTemplateOverloading, CheckOverloadAndNonDeducedArgument)
{
    auto fn = [](std::vector<int>& vec, short s, Index idx)
    {   // 显式特例化 explicit specialization
        int i1 = get_nth<int>(vec, 2);      // 严格匹配
        int i2 = get_nth<int>(vec, s);      // short到int的标准类型转换
        int i3 = get_nth<int>(vec, idx);    // 用户自定义类型转换： Index到int
        
        std::cout << "i1 = " << i1 << std::endl
                  << "i2 = " << i2 << std::endl
                  << "i3 = " << i3 << std::endl;
    };
    
    std::vector<int> fibonacci(10);
    auto generate = [&fibonacci]()
    {
        fibonacci[0] = 1;
        fibonacci[1] = 1;
        for (auto index = 2; index < fibonacci.size(); ++index)
        {
            fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
        }
    };
    generate();
    
    fn(fibonacci, 3, Index(5));
}

TEST(UTest4FnTemplateOverloading, CheckTemplateAlias)
{
    int_exact<8> a = 7;
    EXPECT_EQ(sizeof(a), 1);
    EXPECT_EQ(typeid(a), typeid(char));
}


/*================================================================================================*/

using bin = std::bitset<8>;
 
void show(bin z, const char* s, int n)
{
    if (n == 0) std::cout << "┌─────────┬──────────┐\n";
    if (n <= 2) std::cout << "│ "<<s<<" │ " <<z<<" │\n";
    if (n == 2) std::cout << "└─────────┴──────────┘\n";
}
 
struct A
{
    compl A() { std::cout << "A dtor\n"; }  // compl is a keyword
};
 
TEST(UTest4Misc, CheckTheComplKeyword)
{
    bin x{"01011010"}; show(x, "x      ", 0);
    bin z = compl x;   show(z, "compl x", 2);
    A a;
}