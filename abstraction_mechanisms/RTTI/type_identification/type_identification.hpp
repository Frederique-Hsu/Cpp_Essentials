/*!
 *  \file       type_identification.hpp
 *  \brief      
 *  
 */


#pragma once

#include <cstddef>

namespace my
{
    class type_info
    {
    public:
        virtual ~type_info();
        
        type_info(const type_info&) = delete;
        type_info& operator=(const type_info&) = delete;
    public:
        bool operator==(const type_info&) const noexcept;
        bool operator!=(const type_info&) const noexcept;
        
        bool before(const type_info&) const noexcept;
        std::size_t hash_code() const noexcept;
        const char* name() const noexcept;
    };
}

class Polymorph
{
public:
    Polymorph() = default;
    virtual ~Polymorph() = default;
public:
    virtual void access();
};

class NonPolymorph
{
public:
    NonPolymorph() = default;
    ~NonPolymorph() = default;
public:
    void access();
};

class Derived : public Polymorph
{
public:
    Derived() : Polymorph() {}
    ~Derived() = default;
public:
    void access() override;
};

class NonObject : public NonPolymorph
{
public:
    NonObject() : NonPolymorph() {}
    ~NonObject() = default;
public:
    void access();
};