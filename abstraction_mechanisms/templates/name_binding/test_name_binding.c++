/*!
 *  \file       test_name_binding.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>
#include <algorithm>

#include "test_name_binding.h++"

#include "name_binding.hpp"
#include "test_instantiation_points.hpp"

TEST(UTest4NameBinding, CheckTemplateNameBinding)
{
    std::vector<int> numbers{1, 2, 3, 4, 5};

    int total = sum(numbers);
    EXPECT_EQ(total, 15);

    // auto fn = [](std::vector<Quad>& v)
    // {
    //     Quad total = sum(v);
    //     return total;
    // };
}

TEST(UTest4NameBinding, IntroduceTypeAlias)
{
    std::vector<double> numbers{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

    fct(numbers);
    fct2(numbers);
}

template<typename T>
T* Pool::get()
{
    return new T{42};
}

template<typename T>
void Pool::release(T* obj_ptr)
{
    if (obj_ptr != nullptr)
    {
        delete obj_ptr;
    }
    obj_ptr = nullptr;
}

template<typename Allocator> void access(Allocator& allocator)
{
    int* p = allocator.template get<int>();     // OK: 编译器假定get()是一个模板

    EXPECT_EQ(*p, 42);
    allocator.template release(p);
}

void user(Pool& pool)
{
    access(pool);
}

TEST(UTest4NameBinding, CheckMemberTemplate)
{
    Pool pool;
    user(pool);
}

/*================================================================================================*/

namespace point_of_definition_binding
{
void g(double in)
{
    std::cout << "g(double{" << in << "})" << std::endl;
}

void g2(double in)
{
    std::cout << "g2(double{" << in << "})" << std::endl;
}

template<typename T>
int function(T a)
{
    /*!
     *  \note       Point-of-Definition Binding 定义点绑定
     *  \details    当编译器遇到一个模板定义时，它会判断哪些名字是依赖性的。
     *              如果名字是依赖性的，编译器将查找其声明的工作推迟到实例化时。
     * 
     *              编译器将不依赖于模板实参的名字当作模板外的名字一样处理；因此，在定义点位置这种名字必须在作用域中。
     * 
     *              如果找到了名字的声明，则编译器就会使用这个声明，即使随后可能发现“更好的”声明也是如此。
     *              如下面代码的g(2)的调用， 它只能使用模板函数之前的void g(double)，而不能使用模板函数之后的g(int)。
     *              因为模板定义点绑定在分割着
     *  
     */
    g2(2);      // OK: call g2(double)
    // g3(2);      // Error: no g3() in scope
    g(2);       // OK: call g(double), but not g(int), because g(int) is not in scope

    return static_cast<int>(a);
}

void g(int in)
{
    std::cout << "g(int{" << in << "})" << std::endl;
}

void g3(int in)
{
    std::cout << "g3(int{" << in << "})" << std::endl;
}

TEST(UTest4NameBinding, CheckPointOfDefinitionBinding)
{
    int x = function(15);
    EXPECT_EQ(x, 15);
}
}

/*================================================================================================*/

namespace point_of_instantiation_binding
{
void g(int in)
{
    std::cout << "g(int{" << in << "})" << std::endl;
}

template<typename T> void f(T a)
{
    std::cout << "template<typename T> void f(T a)" << std::endl;

    g(a);
    if (a)
    {
        h(a-1);
    }
}
template<> void f<int>(int a);

void h(int i)
{
    std::cout << "h(int{" << i << "})" << std::endl;

    extern void g(double);
    f(i);
}

template<> void f<int>(int a)
{
    std::cout << "template specialized template<> void f<>(int a = " << a << ")" << std::endl;
}

TEST(UTest4NameBinding, CheckPointOfInstantiationBinding)
{
    h(12345);
}
}

/*================================================================================================*/

namespace {
template<typename T> class Container
{
    std::vector<T> vec;
public:
    Container(const std::initializer_list<T>& init_list);
public:
    void sort();
    void print();
};

template<> class Container<int>
{
    std::vector<int> numbers;
public:
    Container(std::size_t size);
public:
    void assign(const std::initializer_list<int>& nums_list);
    void sort();
    void print();
};

void fn()
{
    Container<int> numbers(15);
    numbers.assign({57, -12, 34, 15, 128, -68, 125, 150, 29});

    numbers.sort();
    numbers.print();
}

TEST(UTest4NameBinding, CheckClassTemplatePointOfInstantiationBinding)
{
    fn();
}

#if false
template<typename T>
Container<T>::Container(const std::initializer_list<T>& init_list)
{
    for (T& elem : init_list)
    {
        vec.push_back(elem);
    }
}

template<typename T>
void Container<T>::sort()
{
    std::sort(vec.begin(), vec.end());
}
#endif

Container<int>::Container(std::size_t size) : numbers(size)
{
}

void Container<int>::assign(const std::initializer_list<int>& nums_list)
{
    if (numbers.size() >= nums_list.size())
    {
        auto index = 0U;
        for (int num : nums_list)
        {
            numbers[index++] = num;
        }
    }
    else // if (numbers.size() < nums_list.size())
    {
        auto size = numbers.size();
        auto index = 0U;
        for (int num : nums_list)
        {
            if (index >= size)
            {
                numbers.push_back(num);
            }
            numbers[index++] = num;
        }
    }
}

void Container<int>::sort()
{
    std::sort(numbers.begin(), numbers.end());
}

void Container<int>::print()
{
    for (int& number : numbers)
    {
        std::cout << number << "  ";
    }
    std::cout << std::endl;
}
}

/*================================================================================================*/

template<typename T, typename S>
void print_sorted(std::vector<T>& vec, S sort, std::ostream& os)
{
    sort(vec.begin(), vec.end());
    for (const T& elem : vec)
    {
        os << elem << "  ";
    }
    os << std::endl;
}

TEST(UTest4NameBinding, CheckPointOfInstantiation)
{
    auto fct = [](std::vector<std::string>& vec)
    {
        using Iter = decltype(vec.begin());
        print_sorted(vec, std::sort<Iter>, std::cout);
    };

    std::vector<std::string> word_vec{"so", "why", "don't", "we", "completely", "avoid", "nonlocal", "names",
                                      "in", "template", "definitions"};
    fct(word_vec);
}