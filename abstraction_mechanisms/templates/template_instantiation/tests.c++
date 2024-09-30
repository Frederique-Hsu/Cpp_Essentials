/*!
 *  \file       tests.c++
 *  \brief      
 *  
 */


#include "MyVector.hpp"

/*!
 *  \attention  Instantiate in this translation unit, use this point of instantiation
 */
template<> class MyVector<char*>;


#include <cstdlib>
#include <cstring>

#include <iostream>
#include <stdexcept>

template<>
class MyVector<char*>
{
    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec);
    friend std::istream& operator>>(std::istream& is,       MyVector& vec);
public:
    MyVector();
    MyVector(const char* str);
    MyVector(const char array[], uint len);
    MyVector(const MyVector& rhs);
    MyVector& operator=(const MyVector& rhs);
    MyVector(MyVector&& rhs);
    MyVector& operator=(MyVector&& rhs);
    ~MyVector();
private:
    char* m_elements;
    std::size_t m_size;
public:
    char& operator[](int index);
    const char& operator[](int index) const;
    std::size_t size() const;
    char* begin();
    char* end();
    const char* toString() const;
};

std::ostream& operator<<(std::ostream& os, const MyVector<char*>& vec)
{
    os << vec.m_elements;
    return os;
}
std::istream& operator>>(std::istream& is,       MyVector<char*>& vec)
{
    is >> vec.m_elements;
    return is;
}
bool operator==(const MyVector<char*>& vec, const char* str)
{
    return std::strcmp(vec.toString(), str) == 0;
}

/*============================================================================*/

// template<>       // 特例化类模板的成员函数在类外部实现时，不需要加上template<>. 加上反而错了。
MyVector<char*>::MyVector() : m_elements{nullptr}, m_size{0}
{
}

MyVector<char*>::MyVector(const char* str) : m_size{std::strlen(str) + 1}
{
    m_elements = static_cast<char*>(std::calloc(m_size, sizeof(char)));
    if (m_elements == nullptr)
    {
        throw std::bad_alloc();
    }
    std::copy(str, str + std::strlen(str), m_elements);
}

MyVector<char*>::~MyVector()
{
    if (m_elements != nullptr)
    {
        std::free(m_elements);
    }
}

std::size_t MyVector<char*>::size() const
{
    return m_size;
}

MyVector<char*>::MyVector(const char array[], uint len) : m_size{static_cast<std::size_t>(len + 1)}
{
    m_elements = (char*)std::calloc(m_size, sizeof(char));
    if (m_elements == nullptr)
    {
        throw std::bad_alloc();
    }
    for (int index = 0; index < len; ++index)
    {
        *(m_elements + index) = array[index];
    }
}

MyVector<char*>::MyVector(const MyVector<char*>& rhs) : m_size{rhs.m_size}
{
    m_elements = static_cast<char*>(std::calloc(m_size, sizeof(char)));
    if (m_elements == nullptr)
    {
        throw std::bad_alloc();
    }
    std::copy(rhs.m_elements, rhs.m_elements + rhs.m_size, m_elements);
}

MyVector<char*>& MyVector<char*>::operator=(const MyVector<char*>& rhs)
{
    if (this != &rhs)
    {
        delete [] m_elements;
        m_elements = nullptr;
        
        m_size = rhs.m_size;
        m_elements = (char*)std::calloc(m_size, sizeof(char));
        std::copy(rhs.m_elements, rhs.m_elements + rhs.m_size, m_elements);
    }
    return *this;
}

MyVector<char*>::MyVector(MyVector<char*>&& rhs) : m_size{rhs.m_size}
{
    m_elements = rhs.m_elements;
    
    rhs.m_elements = nullptr;
    rhs.m_size = 0;
}

MyVector<char*>& MyVector<char*>::operator=(MyVector<char*>&& rhs)
{
    if (this != &rhs)
    {
        delete [] m_elements;
        m_elements = nullptr;
        
        m_size = rhs.m_size;
        m_elements = rhs.m_elements;
        
        rhs.m_elements = nullptr;
        rhs.m_size = 0;
    }
    return *this;
}

char& MyVector<char*>::operator[](int index)
{
    return *(m_elements + index);
}

const char& MyVector<char*>::operator[](int index) const
{
    return *(m_elements + index);
}

char* MyVector<char*>::begin()
{
    return m_elements;
}

char* MyVector<char*>::end()
{
    return m_elements + m_size;
}

const char* MyVector<char*>::toString() const
{
    return m_elements;
}
/*====================================================================================================================*/

#include <gtest/gtest.h>


TEST(UTest4SpecializedMyVector, CheckMyVectorConstructors)
{
    MyVector<char*> empty;
    EXPECT_EQ(empty.size(), 0);
    
    char hello_world[] = "hello_world";
    MyVector<char*> str(hello_world);
    EXPECT_EQ(str.size(), std::strlen(hello_world) + 1);
    
    char array[] = {'h', 'e', 'l', 'l', 'o', '_', 'w', 'o', 'r', 'l', 'd'};
    EXPECT_EQ(sizeof(hello_world)/sizeof(char), sizeof(array)/sizeof(char) + 1);
    
    MyVector<char*> array_vec(array, sizeof(array)/sizeof(char));
    EXPECT_EQ(array_vec.size(), sizeof(array)/sizeof(char) + 1);
}

TEST(UTest4SpecializedMyVector, CheckMyVectorCopyAndAssignmentConstructors)
{
    MyVector<char*> charlie = "Charlie";
    MyVector<char*> charles(charlie);
    
    for (int index = 0; index < charles.size(); ++index)
    {
        std::cout << charles[index];
    }
    std::cout << std::endl;
    EXPECT_EQ(charles, "Charlie");
    
    using EliteName = MyVector<char*>;
    EliteName sam_altmann("Sam Altmann");
    EliteName elon_musk("Elon Musk");
    EXPECT_TRUE(sam_altmann.size() != elon_musk.size());
    
    EliteName tim_cook("Tim Cook");
    tim_cook = elon_musk;
    EXPECT_STREQ(tim_cook.toString(), "Elon Musk");
    
    MyVector<char*> anonymous(std::move(sam_altmann));
    EXPECT_TRUE(sam_altmann.size() == 0);
    EXPECT_TRUE(sam_altmann.begin() == nullptr);
    EXPECT_STREQ(anonymous.toString(), "Sam Altmann");
    
    EliteName bill_gates("Bill Gates");
    bill_gates = std::move(elon_musk);
    EXPECT_STREQ(bill_gates.toString(), "Elon Musk");
    EXPECT_TRUE(elon_musk.size() == 0);
    EXPECT_TRUE(elon_musk.begin() == nullptr);
}

TEST(UTest4SpecializedMyVector, CheckMyVectorIterators)
{
    MyVector<char*> self("MyVector<char*>");
    
    for (auto iter = self.begin(); iter != self.end(); ++iter)
    {
        std::cout << *iter;
    }
    std::cout << std::endl;
    
    assert(std::strcmp(self.toString(), "MyVector<char*>") == 0);
}