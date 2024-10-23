/*!
 *  \file       class_templates.hpp
 *  \brief      
 *  
 */


#pragma once

/*!
 *  \section    Class Templates
 *  
 */

template<typename X>
class Ct
{
public:
    Ct();
private:
    X mem;
public:
    X fn();
    int gc();
    void hp(X);
};

class User;

template<>
class Ct<User>
{
public:
    Ct();
    ~Ct();
private:
    User* mem;
public:
    User fn();
    int gc();
    void hp(User);
    void ko(int);
};

/*================================================================================================*/

/*!
 *  \class      Ptr class template
 *  
 */

template<typename T>
class Ptr
{
private:
    T* ptr;
    std::size_t ref_count;
public:
    Ptr(T* p);
    virtual ~Ptr();
    Ptr(const Ptr& rhs);
    template<typename T2> explicit operator Ptr<T2>();
public:
    T& operator*();
    T* operator->();
};

#include "class_templates_impl.hpp"

