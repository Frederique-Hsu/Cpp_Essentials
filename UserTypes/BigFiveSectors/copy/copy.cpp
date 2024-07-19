/*!
 *  \file       copy.cpp
 *  \brief      
 *  
 */


#include "copy.hpp"

class Descriptor
{
public:
    Descriptor();
};

Descriptor::Descriptor()
{
    /*!
     *  \todo   to be implemented here in the future
     */
}

class Representation
{
public:
    Representation();
};

Representation::Representation()
{
    /*!
     *  \todo   to be implemented
     */
}

Image::Image(Representation* repr, bool is_shared) : m_rep{repr}, m_shared{is_shared}
{
}

/*!
 *  \section    写前拷贝 (copy-on-write) 的概念
 *  \details    其思想就是在共享状态被修改之前，副本其实并不真的需要独立性。因此我们可以推迟共享状态的拷贝，直至首次修改副本前才真正进行拷贝。
 */
Image::Image(const Image& img)      // 进行浅拷贝 (shallow copy)，并准备进行写前拷贝
    : m_rep{img.m_rep}, m_shared{img.m_shared}
{
}

/*!
 *  \attention  为保护传递给拷贝构造函数的参数，我们在修改它之前拷贝Representation
 *              
 *              写前拷贝 copy-on-write 能有效结合深拷贝 (deep copy) 的简单性和浅拷贝 (shallow copy) 的性能。
 */
void Image::write_block(Descriptor d)
{
    if (m_shared == true)
    {
        m_rep = clone();
        m_shared = false;
    }
}

Representation* Image::clone()
{
    return new Representation();
}