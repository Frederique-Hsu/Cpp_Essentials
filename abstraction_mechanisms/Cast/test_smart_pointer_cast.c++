/*!
 *  \file       test_pointer_cast.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>
#include <type_traits>

#include "smart_pointer_cast.hpp"


class Base
{
public:
    Base(int num);
    virtual ~Base();
private:
    int m_element;
public:
    virtual void fn() const;
};

class Derived : public Base
{
public:
    Derived(int num);
    ~Derived();
public:
    void fn() const override;
};

Base::Base(int num) : m_element{num}
{
}

Base::~Base()
{
}

void Base::fn() const
{
    std::cout << "I am from Base!" << std::endl;
}

Derived::Derived(int num) : Base(num)
{
}

Derived::~Derived()
{
}

void Derived::fn() const
{
    std::cout << "I am from Derived!" << std::endl;
}

class UTest4SmartPointerCast : public ::testing::Test
{
public:
    UTest4SmartPointerCast() : base_smart_ptr{std::make_shared<Base>(2)}, 
                               derived_smart_ptr{std::make_shared<Derived>(5)}
    {
    }
    ~UTest4SmartPointerCast()
    {
        std::cout << "Base pointer has come to the reference_count = " << base_smart_ptr.use_count() << std::endl;
        std::cout << "Derived pointer has come to the reference_count = " << derived_smart_ptr.use_count() << std::endl;
    }
protected:
    std::shared_ptr<Base> base_smart_ptr;    
    std::shared_ptr<Derived> derived_smart_ptr;
};

TEST_F(UTest4SmartPointerCast, CheckStaticPointerCast)
{
    std::cout << "Base pointer says: ";
    base_smart_ptr->fn();
    
    std::cout << "Derived pointer says: ";
    derived_smart_ptr->fn();
    
    // static_pointer_cast to go up to parent class hierarchy
    auto base_ptr = my::static_pointer_cast<Base>(derived_smart_ptr);
    base_ptr->fn();
    
    EXPECT_EQ(typeid(base_smart_ptr), typeid(base_ptr));
}

TEST_F(UTest4SmartPointerCast, CheckDynamicPointerCast)
{
    std::cout << "Base pointer says: ";
    base_smart_ptr->fn();
    
    std::cout << "Derived pointer says: ";
    derived_smart_ptr->fn();
    
    // dynamic_pointer_cast to go up/down/even cross class hierarchy
    if (auto downcast_dynamic_ptr = my::dynamic_pointer_cast<Derived>(base_smart_ptr))
    {
        std::cout << "The downcasted pointer says: ";
        downcast_dynamic_ptr->fn();
    }
    else if (auto upcast_dynamic_ptr = my::dynamic_pointer_cast<Base>(derived_smart_ptr))
    {
        std::cout << "The upcasted pointer says: ";
        upcast_dynamic_ptr->fn();
    }
}

#if false
TEST_F(UTest4SmartPointerCast, CheckConstPointerCast)
{
    const std::shared_ptr<Derived> derived_const_ptr{std::make_shared<Derived>(15)};    
    EXPECT_EQ(std::is_const<decltype(derived_const_ptr)>::value, true);
    
    std::shared_ptr<Derived> derived_ptr = my::const_pointer_cast<Derived>(derived_const_ptr);
    EXPECT_EQ(std::is_const<decltype(derived_ptr)>::value, false);
}
#endif