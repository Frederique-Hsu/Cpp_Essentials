/*!
 *  \file       dynamic_polymorphism.hpp
 *  \brief      
 *  
 */


#pragma once

namespace dynamic_polymorphism
{
    class base
    {
    public:
        base() {}
        virtual ~base() {}
    public:
        virtual void doWork() = 0;
    };
    
    class derived : public base
    {
    public:
        derived() = default;
        ~derived() = default;
    public:
        void doWork() override;
    };
}