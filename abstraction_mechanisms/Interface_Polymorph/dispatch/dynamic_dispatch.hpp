/*!
 *  \file       dynamic_dispatch.hpp
 *  \brief      
 *  
 */


namespace dynamic_dispatch
{
    class Circle;
    class Triangle;
    
    class Shape
    {
    public:
        virtual ~Shape() = default;
    public:
        virtual bool intersect(const Shape&) const = 0;
        virtual bool intersect(const Circle&) const = 0;
        virtual bool intersect(const Triangle&) const = 0;
    };
    
    class Circle : public Shape
    {
    public:
        bool intersect(const Shape&) const override;
        virtual bool intersect(const Circle&) const override;
        virtual bool intersect(const Triangle&) const override;
    };
    
    class Triangle : public Shape
    {
    public:
        bool intersect(const Shape&) const override;
        virtual bool intersect(const Circle&) const override;
        virtual bool intersect(const Triangle&) const override;
    };
    
    void intersect(Shape& s1, Shape& s2);
}