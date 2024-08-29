/*!
 *  \file   Triangle.cpp
 *  \brief  
 *  
 */


#include "Triangle.hpp"

#include <cmath>
#include <cstdlib>

Triangle::Triangle(Point p1, Point p2, Point p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{
    /* error: call to non-'constexpr' function 'bool operator!=(const Point&, const Point&)' */
    // static_assert(p1 != p2, "Two points are actually the same point.");     
    // static_assert(p2 != p3, "Two points are actually the same point.");
    // static_assert(p1 != p3, "Two points are actually the same point.");

    double a = distance(p2, p3), b = distance(p1, p3), c = distance(p1, p2);
    // static_assert(a + b > c, "Sum of two sides MUST be 3rd side in any triangle.");
    // static_assert(b + c > a, "Sum of two sides MUST be 3rd side in any triangle.");
    // static_assert(a + c > b, "Sum of two sides MUST be 3rd side in any triangle.");
}

/*!
 *  \brief      The area of a triangle
 *  \details    已知三角形的三个顶点坐标，求三角形的面积。
 *  \param      none
 *  \return     the area
 */
double Triangle::area()
{
    long long intermediate_result = m_p1.x() * (m_p2.y() - m_p3.y()) + 
                                    m_p2.x() * (m_p3.y() - m_p1.y()) +
                                    m_p3.x() * (m_p1.y() - m_p2.y());
    return std::abs(intermediate_result) / 2.0;
}

/*!
 *  \brief      The perimeter of a triangle
 *  \details    已知三角形的三个顶点坐标，求三角形的周长
 *  \param      none
 *  \return     the perimeter
 */
double Triangle::perimeter()
{
    double a = distance(m_p1, m_p2), b = distance(m_p2, m_p3), c = distance(m_p1, m_p3);
    return a + b + c;
}

/*!
 *  \brief      The gravity center of a triangle
 *  \details    已知三角形的三个顶点坐标，求三角形的重心，即三条边的中线交于一点。
 *  \param      none
 *  \return     the gravity center point
 */
Point Triangle::gravity_center_point() const
{
    double center_x = (m_p1.x() + m_p2.x() + m_p3.x()) / 3.0;
    double center_y = (m_p1.y() + m_p2.y() + m_p3.y()) / 3.0;
    return Point(static_cast<int>(center_x), static_cast<int>(center_y));
}

/*!
 *  \brief      The inner center of a triangle
 *  \details    已知三角形的三个顶点坐标，求三角形的内心，即三条边的高线交于一点。
 *  \param      none
 *  \return     the inner center point
 */
Point Triangle::inner_center_point()
{
    double a = distance(m_p2, m_p3),
           b = distance(m_p1, m_p3),
           c = distance(m_p1, m_p2);
    double perimeter = a + b + c;

    double center_x = (a * m_p1.x() + b * m_p2.x() + c * m_p3.x()) / perimeter;
    double center_y = (a * m_p1.y() + b * m_p2.y() + c * m_p3.y()) / perimeter;

    return Point(static_cast<int>(center_x), static_cast<int>(center_y));
}

/*!
 *  \brief      The circum center of a triangle
 *  \details    已知三角形的三个顶点坐标，求三角形的外心，即外接圆的圆心。
 *  \param      none
 *  \return     the circum center point.
 */
Point Triangle::circum_center_point()
{
    double a1 = 2.0 * (m_p2.x() - m_p1.x()),
           b1 = 2.0 * (m_p2.y() - m_p1.y()),
           c1 = m_p2.x() * m_p2.x() + m_p2.y() * m_p2.y() - m_p1.x() * m_p1.x() - m_p1.y() * m_p1.y();
    
    double a2 = 2.0 * (m_p3.x() - m_p2.x()),
           b2 = 2.0 * (m_p3.y() - m_p2.y()),
           c2 = m_p3.x() * m_p3.x() + m_p3.y() * m_p3.y() - m_p2.x() * m_p2.x() - m_p2.y() * m_p2.y();
    
    double center_x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    double center_y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    return Point(static_cast<int>(center_x), static_cast<int>(center_y));
}

/*!
 *  \brief      The ortho center of a triangle
 *  \details    已知三角形的三个顶点坐标，求三角形的垂心，即内切圆的圆心
 *  \param      none
 *  \return     the ortho center point
 */
Point Triangle::ortho_center_point()
{
    double a1 = m_p2.x() - m_p3.x();
    double b1 = m_p2.y() - m_p3.y();
    double c1 = a1 * m_p1.y() - b1 * m_p1.x();
    
    double a2 = m_p1.x() - m_p3.x();
    double b2 = m_p1.y() - m_p3.y();
    double c2 = a2 * m_p2.y() - b2 * m_p2.x();

    double center_x = (a1 * c2 - a2 * c1) / (a2 * b1 - a1 * b2);
    double center_y = (b1 * c2 - b2 * c1) / (a2 * b1 - a1 * b2);
    return Point(static_cast<int>(center_x), static_cast<int>(center_y));
}

Point Triangle::center() const
{
    return gravity_center_point();
}

void Triangle::move(Point to)
{
    m_p1 = to;
}

void Triangle::draw() const
{
}

void Triangle::rotate(int angle)
{
}