/*!
 *  \file       multiple_inheritance_casting.cpp
 *  \brief
 *
 */


#include "multiple_inheritances_casting.hpp"

#include <typeindex>

void Component::communicate()
{
}

Receiver::Receiver() : Component()
{
}

Receiver::~Receiver()
{
}

std::string Receiver::read()
{
    return std::string("Received the message");
}

Transmitter::Transmitter(const std::string& msg) : Component(), m_msg{msg}
{
}

Transmitter::~Transmitter()
{
}

void Transmitter::write(const std::string& msg)
{
}

Radio::Radio(const std::string& message) : Receiver(), Transmitter(message)
{
}

Radio::~Radio()
{
}

void Radio::communicate()
{
}

void cast(Radio& ref_radio)
{
    IStorable* ptr_store = &ref_radio;

    Component* ptr_component = dynamic_cast<Component*>(ptr_store); // 此处有歧义性，因为一个Radio包含两个Component
    if (ptr_component == nullptr)
    {
        throw std::bad_cast();
    }
    ptr_component->communicate();
}

void cast(IStorable* ptr_store)
{
    if (Component* ptr_component = dynamic_cast<Component*>(ptr_store))
    {   // 以为得到了一个Component对象
        ptr_component->write("Transmitting the message");
    }
    else
    {   // 其实，因为二义性，得到的是一个空的Component对象。
        throw std::bad_cast();
    }
}

/*!
 *  \footnote   只有虚基类进行dynamic_cast转换时才需要进行二义性检查。
 *              对于普通基类，当进行downcast(父类转换成子类)时，其结果只可能是唯一的子对象，或者转换失败。
 *              对虚基类来说，进行upcast(从子类转换成父类)时可能发生类似的二义性问题，但这种二义性可以在编译时被捕获。
 *
 *  \remark     对于上述的多继承有重复的父类Component的情形，dynamic_cast的二义性问题，则通常在编译时无法检查出来。
 */