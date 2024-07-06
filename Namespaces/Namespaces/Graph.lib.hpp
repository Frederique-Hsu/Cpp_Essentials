/*!
 *  \file       Graph.lib.hpp
 *  \brief      Organize the Graph library.
 *
 */


#pragma once


namespace GraphLib
{
class Shape
{
};

class Line : public Shape
{
};

class PolyLine : public Shape
{
};

class Text : public Shape
{
};

Shape operator+(const Shape&, const Shape&);

class GraphReader
{
};

GraphReader open(const char*);
}
