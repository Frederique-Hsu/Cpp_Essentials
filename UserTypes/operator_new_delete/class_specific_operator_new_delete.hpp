/*!
 *  \file       class_specific_operator_new_delete.hpp
 *  \brief
 *
 */


#pragma once

#include "operator_new_delete.hpp"

#include <string>

class Employee
{
public:
    static void* operator new(size_t size);
    static void  operator delete(void* ptr);

    static void* operator new[](size_t size);
    static void  operator delete[](void* ptr);

    static void* operator new(size_t, void* placement_ptr) noexcept;
    static void  operator delete(void* ptr, void* placement_ptr) noexcept;

    static void* operator new[](size_t, void* placement_ptr) noexcept;
    static void  operator delete[](void* ptr, void* placement_ptr) noexcept;

    static void* operator new(size_t size, align_val_t alignment);
    static void  operator delete(void* ptr, align_val_t alignment);

    static void* operator new[](size_t size, align_val_t alignment);
    static void  operator delete[](void* ptr, align_val_t alignment);
public:
    Employee(unsigned id = 0, const std::string& name = "", const std::string& department = "");
    ~Employee();
private:
    unsigned m_id;
    std::string m_name;
    std::string m_department;
public:
    unsigned& Id();
    std::string& Name();
    std::string& Department();

    const unsigned& Id() const;
    const std::string& Name() const;
    const std::string& Department() const;

    void ChangeDepartment(const std::string& new_department);
};