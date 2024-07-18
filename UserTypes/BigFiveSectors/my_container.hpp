/*!
 *  \file       my_container.hpp
 *  \brief
 *
 */


#include <initializer_list>
#include <memory>

namespace my
{

template<class T>
class Container
{
public:
    explicit Container(int size = 0, T init_value = T{});
    Container(std::initializer_list<T> elements);
    virtual ~Container();

private:
    int m_size;
    T* m_element_array;

public:
    int size() const;
    T operator[](unsigned int index) const;
    T* begin() const;
    T* end() const;
};

}   // namespace my


/*================================================================================================*/

template<class T>
my::Container<T>::~Container()
{
    if (m_element_array != nullptr)
    {
        delete [] m_element_array;
        m_element_array = nullptr;
    }
}

template<class T>
my::Container<T>::Container(int size, T init_value) : m_size{size}, m_element_array{nullptr}
{
    if (size > 0)
    {
        m_element_array = new T[m_size];

        for (int index = 0; index < m_size; ++index)
        {
            *(m_element_array + index) = init_value;
        }
    }
}

template<class T>
my::Container<T>::Container(std::initializer_list<T> elements)
    : m_size{elements.size()}, m_element_array{nullptr}
{
    if (m_size > 0)
    {
        m_element_array = new T[m_size];

        std::uninitialized_copy(elements.begin(), elements.end(), m_element_array);
    }
}

template<class T>
int my::Container<T>::size() const
{
    return m_size;
}

template<class T>
T my::Container<T>::operator[](unsigned int index) const
{
    return *(m_element_array + index);
}

template<class T>
T* my::Container<T>::begin() const
{
    return m_element_array;
}

template<class T>
T* my::Container<T>::end() const
{
    return (m_element_array + m_size);
}
