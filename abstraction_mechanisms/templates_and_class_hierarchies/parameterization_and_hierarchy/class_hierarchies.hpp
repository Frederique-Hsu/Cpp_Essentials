/*!
 *  \file       class_hierarchies.hpp
 *  \brief      
 *  
 */


#pragma once

/*!
 *  \section    Class Hierarchies
 *  
 */

class X
{
public:
};


class Cx
{
public:
    Cx();
private:
    X mem;
public:
    virtual X& fn();
    virtual int gc();
    virtual void hp(X&);
};

class Dcheck : public Cx
{
public:
    Dcheck();
public:
    X& fn() override;
    int gc() override;
    void hp(X&) override;
};

class Duser : public Cx
{
public:
    Duser();
private:
    Duser* ptr;
public:
    X& fn() override;
    int gc() override;
    void hp(X&) override;
    void ko(int);
};

/*================================================================================================*/

namespace generated_types
{
    class Shape
    {
    public:
        virtual ~Shape() {}
    public:
        virtual void draw();
    };

    struct Point
    {
        int x_coord;
        int y_coord;
    };

    class Triangle : public Shape
    {
    public:
        Triangle(const Point& a, const Point& b, const Point& c);
        ~Triangle() {}
    private:
        Point three_points[3];
    public:
        virtual void draw() override;
    };

    class Circle : public Shape
    {
    public:
        Circle();
        Circle(const Point& center, double radius);
        ~Circle() {}
    private:
        Point m_center;
        double m_radius;
    public:
        virtual void draw() override;
    };
}