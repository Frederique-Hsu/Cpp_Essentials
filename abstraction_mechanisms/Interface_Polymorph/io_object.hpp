/*!
 *  \file       io_object.hpp
 *  \brief      
 *  
 */


#pragma once

#include <iostream>

class IOObject
{
public:
    virtual ~IOObject() = default;
    
    virtual IOObject* clone() const = 0;
};

class UnknownObject
{
public:
};

using PtrFn = IOObject* (*)(std::istream&);

std::string get_word(std::istream& is);

IOObject* get_obj(std::istream& is, std::string& str);

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;
    
    virtual void draw();
};

class Circle : public Shape
{
public:
    Circle(std::istream&) : Shape() {}
    ~Circle() = default;
public:
    void draw() override;
};

class Triangle : public Shape
{
public:
    Triangle(std::istream&) : Shape() {}
    ~Triangle() = default;
public:
    void draw() override;
};

class IOCircle : public Circle, public IOObject
{
public:
    IOCircle(std::istream&);
    ~IOCircle() = default;
public:
    IOCircle* clone() const override;
    static IOObject* new_circle(std::istream& is);
};

class IOTriangle : public Triangle, public IOObject
{
public:
    IOTriangle(std::istream&);
    ~IOTriangle() = default;
public:
    IOTriangle* clone() const override;
    static IOObject* new_triangle(std::istream& is);
};