/*!
 *  \file       function_template_overloading_impl.hpp
 *  \brief      
 *  
 */

double sqrt(double number)
{
    // return std::sqrt(number);       // 如果这样来处理的话，会带来 infinite recursion call 的错误，因为在标准库中不存在 
                                       // std::sqrt(double)的普通函数，只存在 std::sqrt(float), std::sqrt(long double) 普通函数，
                                       // 和 sqrt<T>(T) 的函数模板。 所以要做如下的转换。
    return std::sqrt(static_cast<long double>(number));
}

template<typename T> T sqrt(T num)
{
    return std::sqrt(num);
}

template<typename T>
std::complex<T> sqrt(std::complex<T> z)
{
    auto mod = std::sqrt(std::pow(z.real(), 2) + std::pow(z.imag(), 2));
    return std::complex<T>{z.real()/mod, z.imag()/mod};
}

template<typename T>
Base<T>::Base(T elem) : m_elem{elem}
{
}

template<typename T>
Derived<T>::Derived(T elem, bool (*checking)(T)) : Base<T>{elem}, m_checker{checking}
{
}

template<typename T>
bool Base<T>::execute()
{
    std::cout << "Base<T> object_ptr is executing..." << std::endl;
    return bool{};
}

template<typename T>
bool Derived<T>::execute()
{
    std::cout << "Derived<T> object_ptr is executing..." << std::endl;
    return m_checker(Base<T>::m_elem);
}

template<typename T> bool execute(Base<T>* pobj)
{
    return pobj->execute();
}

template<typename T, typename Container> T get_nth(const Container& container, int n)
{
    for (auto index = 0; index < container.size(); ++index)
    {
        if (index == n)
        {
            return container.at(index);
        }
    }
    return T{};
}


Index::Index(int i) : idx{i}
{
}

Index::operator int()
{
    return idx;
}