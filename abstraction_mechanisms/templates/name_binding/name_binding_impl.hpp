/*!
 *  \file       name_binding_impl.hpp
 *  \brief      
 *  
 */


#include <iostream>


template<typename T>
T sum(std::vector<T>& vec)
{
    T t{};
    if (tracing)
    {
        std::cerr << "sum(" << &vec << ")" << std::endl;
    }
    for (int index = 0; index < vec.size(); ++index)
    {
        t += vec[index];
    }
    return t;
}

template<typename Container> 
void fct(Container& container)
{
    typename Container::value_type v1 = container[0];   // OK: 显式说明value_type是类型
    auto v2 = container[1];     // OK: 让编译器推断

    std::cout << v1 << ", " << v2 << std::endl;
}

template<typename Container> 
void fct2(Container& container)
{
    Value_Type<Container> v1 = container[0];    // OK: 通过引入类型别名来避免使用typename的尴尬
    std::cout << v1 << std::endl;
}