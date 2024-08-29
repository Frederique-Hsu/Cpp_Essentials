/*!
 *  \file       static_dynamic_cast.hpp
 *  \brief
 *
 */


#pragma once

#include "multiple_inheritances_casting.hpp"

/*!
 *  \section    static_cast vs. dynamic_cast
 *
 *  \brief      dynamic_cast可以从一个多态虚基类转换到一个派生类或者一个兄弟类
 *              static_cast则不行，因为它不检查转换的对象.
 */

#include <CppUTest/TestHarness.h>


TEST_GROUP(UTest4StaticVersusDynamicCast)
{
    /*!
     *  \attention  dynamic_cast要求转换对象是多态的，因为它需要特定的信息来找到基类的子对象。
     *              而一个非多态对象中不包含任何这样的信息。
     *              为什么还有人要用static_cast在类层次之间进行转换导航呢？ 原因在于dynamic_cast是
     *              有运行时额外开销的。只要条件允许，尽量使用更安全，运行时进行检查的dynamic_cast。
     */
    void static_versus_dynamic_cast(Radio& ref_radio)
    {
        Receiver* ptr_receiver = &ref_radio;    // Receiver是Radio的普通基类
        Radio* ptr_radio = static_cast<Radio*>(ptr_receiver);   // OK: 无须检查
        ptr_radio = dynamic_cast<Radio*>(ptr_receiver);         // OK: downcast运行时检查


        IStorable* ptr_store = &ref_radio;      // IStorable是Radio的虚基类
        // ptr_radio = static_cast<Radio*>(ptr_store);     // error: 不能从虚基类转换
        ptr_radio = dynamic_cast<Radio*>(ptr_store);        // OK; 运行时检查
    }

    /*!
     *  \attention  对于一个void*所指向的内存，编译器不能做任何假设。这意味着dynamic_cast不能将一个
     *              void*转换为其他类型，因为dynamic_cast必须探查一个对象的内部来确定其类型。
     *              这时需要使用static_cast来强制转换，不做任何类型安全检查的。
     */
    Radio* cast_from_void_ptr_to_object_ptr(void* ptr)
    {
        IStorable* ptr_store = static_cast<IStorable*>(ptr);    // 此强制转换其安全可靠性只能信任程序员
        return dynamic_cast<Radio*>(ptr_store);
    }
};

