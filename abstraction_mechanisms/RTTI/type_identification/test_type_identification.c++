/*!
 *  \file       test_type_identification.c++
 *  \brief      
 *  
 */


#include <CppUTest/TestHarness.h>

#include <iostream>
#include <typeinfo>
#include <typeindex>

#include "type_identification.hpp"

TEST_GROUP(UTest4TypeInfoAndTypeId)
{
};

    class Shape
    {
    public:
        virtual ~Shape() = default;
    public:
        virtual void draw() = 0;
    };
    
    class Circle : public Shape
    {
    public:
        Circle(int radius) : Shape(), m_radius{radius} {}
        ~Circle() = default;
    private:
        int m_radius;
    public:
        void draw() override
        {
            std::cout << "drawing a circle" << std::endl;
        }
    };
    
    class Triangle : public Shape
    {
    public:
        Triangle(int a, int b, int c) : Shape(), edge_a{a}, edge_b{b}, edge_c{c} {}
        ~Triangle() = default;
    private:
        int edge_a;
        int edge_b;
        int edge_c;
    public:
        void draw() override
        {
            std::cout << "drawing a triangle" << std::endl;
        }
    };
    
TEST(UTest4TypeInfoAndTypeId, CheckTypeInfoAndTypeId)
{
    auto acquire = [] (Shape& ref_shape, Shape* ptr_shape)
    {
        std::cout << std::endl;
        std::cout << typeid(ref_shape).name() << std::endl;
        std::cout << typeid(*ptr_shape).name() << std::endl;
        std::cout << typeid(ptr_shape).name() << std::endl;
    };
    
    Circle circle(2);
    Shape& ref_shape = circle;
    Shape* ptr_shape = new Triangle(1, 2, 3);
    
    acquire(ref_shape, ptr_shape);
    delete ptr_shape;
    
    ptr_shape = nullptr;
    // CHECK_THROWS(std::bad_typeid, typeid(ptr_shape));
    try
    {
        std::cout << "The type name is " << typeid(ptr_shape).name() << std::endl;
    }
    catch (std::bad_typeid& exception)
    {
        std::cout << "An exception: " << exception.what() << " was captured.\n" << std::endl;
    }
}

TEST(UTest4TypeInfoAndTypeId, CheckPolymorphClassTypeInfo)
{
    std::cout << std::endl;
    auto fn = [](NonPolymorph& ref_nonpoly, Polymorph& ref_poly)
    {
        try
        {
            std::cout << typeid(ref_nonpoly).name() << std::endl;
            std::cout << typeid(ref_poly).name() << std::endl;
        }
        catch (std::bad_typeid& exception)
        {
            std::cout << "The exception " << exception.what() << " was captured." << std::endl;
        }
        catch (...)
        {
            std::cout << "The segment fault exception was captured." << std::endl;
        }
    };
    
        Derived poly_obj;
        NonObject non_obj;
        
        fn(non_obj, poly_obj);
        // fn(*static_cast<NonPolymorph*>(nullptr), *static_cast<Polymorph*>(nullptr));
}

TEST(UTest4TypeInfoAndTypeId, CheckHowToUtilizeRTTICorrectly)
{
    std::cout << std::endl;
    auto rotate = [](const Shape& cref_shape)
    {
        Shape& ref_shape = const_cast<Shape&>(cref_shape);
        if (typeid(ref_shape) == typeid(Circle))
        {
            ref_shape.draw();
        }
        else if (typeid(ref_shape) == typeid(Triangle))
        {
            ref_shape.draw();
        }
    };
    
    Circle circle(3);
    Triangle triangle(2, 4, 5);
    
    rotate(circle);
    rotate(triangle);
}