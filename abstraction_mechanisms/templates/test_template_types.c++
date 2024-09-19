/*!
 *  \file       test_template_types.c++
 *  \brief      
 *  
 */


#include "test_template_types.h++"

#include <vector>
#include <gtest/gtest.h>

TEST(UTest4TemplateTypes, CheckTypeEquivalence)
{
    using std::vector;
    
    class Shape
    {
    public:
        virtual ~Shape() = default;
    };
    
    class Circle : public Shape
    {
    public:
        Circle(int radius) : Shape(), m_radius{radius} {}
        virtual ~Circle() = default;
    private:
        int m_radius;
    };
    
    Shape* ptr{new Circle(100)};    // OK: Circle* converts to Shape*
    
    /*!
     *  \attention  对一个模板使用不同模板实参生成的类型是不同类型。
     *              特别是， 用相关实参生成的类型不一定是相关的， 如下例子：
     */
    // vector<Shape>* q{new vector<Circle>{}};     // Error: no vector<Circle>* to vector<Shape>* conversion.
    // vector<Shape> vs{vector<Circle>{}};         // Error: vector<Circle> cannot be converted to vector<Shape>
    // vector<Shape*> vsptr{vector<Circle*>{}};    // Error: vector<Circle*> cannot be converted to vector<Shape*>
    
    delete ptr;
}