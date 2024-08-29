/*!
 *  \file       test_dynamic_cast_reference.cpp
 *  \brief
 *
 */


#include "test_dynamic_cast_reference.hpp"

#include <iostream>

int TEST_GROUP_CppUTestGroupUTest_DynamicCastForObjectPointer::castFromObjectPointer(Ival_box* pbox)
{
    if (Ival_slider* pslider = dynamic_cast<Ival_slider*>(pbox))
    {
        return pslider->get_value();
    }
    else
    {
        throw std::bad_cast();
    }
}

auto TEST_GROUP_CppUTestGroupUTest_DynamicCastForObjectPointer::castFromObjectReference(Ival_box& rbox)
{
    try
    {
        Ival_slider& rslider = dynamic_cast<Ival_slider&>(rbox);
        return rslider.get_value();
    }
    catch (std::bad_cast& exception)
    {
        throw exception;
    }
}

TEST(UTest_DynamicCastForObjectPointer, CheckIfCastNullPointer)
{
    Ival_box* pslider = new BB_ival_slider();
    auto value = castFromObjectPointer(pslider);
    CHECK_EQUAL(value, 0);
    delete pslider;

    try
    {
        castFromObjectPointer(nullptr);
    }
    catch (std::bad_cast& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
}

TEST(UTest_DynamicCastForObjectPointer, CheckIfCastReference)
{
    BB_ival_slider bbslider;
    auto value = castFromObjectReference(bbslider);
    CHECK(value == 0);
}

void TEST_GROUP_CppUTestGroupUTest_DynamicCastForObjectPointer::castFromPointerOrReference(
    BB_ival_slider& slider, BB_ival_dial& dial)
{
    try
    {
        auto pslider_value = castFromObjectPointer(&slider);
        auto rslider_value = castFromObjectReference(slider);

        CHECK(pslider_value == rslider_value);

        auto pdial_value = castFromObjectPointer(&dial);
        auto rdial_value = castFromObjectReference(dial);

        CHECK(pdial_value == rdial_value);
    }
    catch (std::bad_cast& bad_cast_exception)
    {
        std::cerr << "Captured the bad_cast exception: " << bad_cast_exception.what() << std::endl;
    }
    catch (std::exception& general_exception)
    {
        std::cerr << "Captured the general exception: " << general_exception.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Some misc. exception were captured now." << std::endl;
    }
}

TEST(UTest_DynamicCastForObjectPointer, CheckWhetherCastingPointerReferenceWillThrowException)
{
    std::cout << std::endl;

    BB_ival_slider slider;
    BB_ival_dial dial(50);

    castFromPointerOrReference(slider, dial);
}