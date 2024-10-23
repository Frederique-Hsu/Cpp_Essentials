/*!
 *  \file       test_template_conversions.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "class_templates.hpp"
#include "class_hierarchies.hpp"

TEST(UTest4TemplateConversions, CheckHowToConvertTemplateTypes)
{
    using namespace generated_types;

    auto fn = [](Ptr<Circle>& pcircle)
    {
        Ptr<Shape> pshape{pcircle};     // convert from Ptr<Circle> to Ptr<Shape>
        pshape->draw();

        Ptr<Circle> pcircle2{pshape};   // convert from Ptr<Shape> to Ptr<Circle>
        pcircle2->draw();
    };

    Ptr<Circle> circle_ptr(new Circle(Point{3, 5}, 8));
    fn(circle_ptr);
}
