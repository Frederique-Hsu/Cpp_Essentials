/*!
 *  \file       class_specific_operator_new_delete.cpp
 *  \brief
 *
 */


#include "class_specific_operator_new_delete.hpp"

#include <iostream>

Employee::Employee(unsigned id, const std::string& name, const std::string& department)
    : m_id{id}, m_name{name}, m_department{department}
{
    std::cout << "Constructor Employee::Employee(id = " << m_id
              << ", name = " << m_name
              << ", department = " << m_department << ")"
              << std::endl;
}

Employee::~Employee()
{
    std::cout << "Destructor Employee::~Employee()" << std::endl;
}

unsigned& Employee::Id()
{
    return m_id;
}

std::string& Employee::Name()
{
    return m_name;
}

std::string& Employee::Department()
{
    return m_department;
}

const unsigned& Employee::Id() const
{
    return m_id;
}

const std::string& Employee::Name() const
{
    return m_name;
}

const std::string& Employee::Department() const
{
    return m_department;
}

void Employee::ChangeDepartment(const std::string& new_department)
{
    m_department = new_department;
}

void* Employee::operator new(size_t size)
{
    printf("static void* Employee::operator new(size_t size), size = %ld bytes\n", size);

    return ::operator new(size);    // 此处务必使用::operator new，以表明是调用全局的operator new
}

void Employee::operator delete(void* ptr)
{
    printf("static void Employee::operator delete(void* ptr), ptr = %p\n", ptr);

    return ::operator delete(ptr);  // 同上，此处务必使用::operator delete，调用全局的operator delete
}

void* Employee::operator new[](size_t size)
{
    printf("static void* Employee::operator new[](size_t size), size = %ld bytes\n", size);

    return ::operator new[](size);
}

void Employee::operator delete[](void* ptr)
{
    printf("static void Employee::operator delete[](void* ptr), ptr = %p\n", ptr);

    return ::operator delete[](ptr);
}

void* Employee::operator new(size_t size, void* placement_ptr) noexcept
{
    printf("static void* Employee::operator new(size_t size, void* placement_ptr), "
           "size = %ld bytes, placement_ptr = %p\n", size, placement_ptr);

    return ::operator new(size, placement_ptr);
}

void Employee::operator delete(void* ptr, void* placement_ptr) noexcept
{
    printf("static void Employee::operator delete(void* ptr, void* placement_ptr), "
           "ptr = %p, placement_ptr = %p\n", ptr, placement_ptr);

    return ::operator delete(ptr, placement_ptr);
}

void* Employee::operator new[](size_t size, void* placement_ptr) noexcept
{
    printf("static void* Employee::operator new[](size_t size, void* placement_ptr), "
           "size = %ld bytes, placement_ptr = %p\n", size, placement_ptr);

    return ::operator new[](size, placement_ptr);
}

void Employee::operator delete[](void* ptr, void* placement_ptr) noexcept
{
    printf("void Employee::operator delete[](void* ptr, void* placement_ptr), "
           "ptr = %p, placement_ptr = %p\n", ptr, placement_ptr);

    return ::operator delete[](ptr, placement_ptr);
}

void* Employee::operator new(size_t size, align_val_t alignment)
{
    printf("void* Employee::operator new(size_t size, align_val_t alignment), "
           "size = %ld bytes, alignment = %zu\n", size, static_cast<size_t>(alignment));

    return ::operator new(size, alignment);
}

void Employee::operator delete(void* ptr, align_val_t alignment)
{
    printf("void Employee::operator delete(void* ptr, align_val_t alignment), "
           "ptr = %p, alignment = %zu\n", ptr, static_cast<size_t>(alignment));

    return ::operator delete(ptr, alignment);
}

void* Employee::operator new[](size_t size, align_val_t alignment)
{
    printf("void* Employee::operator new[](size_t size, align_val_t alignment), "
           "size = %ld bytes, alignment = %zu\n", size, static_cast<size_t>(alignment));

    return ::operator new[](size, alignment);
}

void Employee::operator delete[](void* ptr, align_val_t alignment)
{
    printf("void Employee::operator delete[](void* ptr, align_val_t), "
           "ptr = %p, alignment = %zu\n", ptr, static_cast<size_t>(alignment));

    return ::operator delete[](ptr, alignment);
}