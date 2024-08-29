/*!
 *  \file       test_dynamic_cast_reference.hpp
 *  \brief
 *
 */


#pragma once

#include <CppUTest/TestHarness.h>

#include "dynamic_cast.hpp"

TEST_GROUP(UTest_DynamicCastForObjectPointer)
{
    int castFromObjectPointer(Ival_box* pbox);
    auto castFromObjectReference(Ival_box& rbox);

    void castFromPointerOrReference(BB_ival_slider& slider,
                                    BB_ival_dial& dial);
};