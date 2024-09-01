/*!
 *  \file       test_type_cast.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include <typeindex>
#include <typeinfo>

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

TEST(UTest4ExtendedTypeInfo, CheckHowExtendedTypeInfoWorks)
{
    class Icon
    {
    public:
    };
    
    std::unordered_map<std::type_index, Icon> icon_table{
        std::pair<std::type_index, Icon>{std::type_index(typeid(Icon)), Icon()}
    };
    
    auto gc = [&icon_table](Shape* ptr_shape)
    {
        Icon& icon = icon_table[std::type_index{typeid(*ptr_shape)}];
        return icon;
    };
    
        
    Shape* ptr_circle = new Circle(3);
    std::type_index circle_index = std::type_index(typeid(*ptr_circle));
    std::cout << circle_index.name() << std::endl;
    
    Icon icon = gc(ptr_circle);
    
    delete ptr_circle;
}