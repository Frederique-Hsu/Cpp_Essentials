/*!
 *  \file       test_select.cc
 *  \brief      
 *  
 */


#include "select.hpp"

#include <boost/test/unit_test.hpp>

#include <type_traits>
#include <string>
#include <bitset>
#include <cstdint>


BOOST_AUTO_TEST_SUITE(UTest4Select)

    BOOST_AUTO_TEST_CASE(CheckConditional)
    {
        class Shape
        {
        public:
            virtual ~Shape() = default;
        public:
            virtual void draw() = 0;
        };

        struct Point
        {
            int x_coord;
            int y_coord;
        };

        class Circle : public Shape
        {
        public:
            Circle() : m_center{0, 0}, m_radius{1.0} {}
            Circle(Point center, double radius) : m_center{center}, m_radius{radius} {}
            ~Circle() = default;
        private:
            [[maybe_unused]] Point m_center;
            [[maybe_unused]] double m_radius;
        public:
            virtual void draw() override
            {
                std::cout << "Circle::draw()" << std::endl;
            }
        };

        class Triangle : public Shape
        {
        public:
            Triangle(const Point& a, const Point& b, const Point& c) : m_points{a, b, c} {}
            ~Triangle() = default;
        private:
            [[maybe_unused]] Point m_points[3];     // 'maybe_unused' attribute is a C++17 extension
        public:
            virtual void draw() override
            {
                std::cout << "Triangle::draw()" << std::endl;
            }
        };

        typename my::conditional<!std::is_polymorphic<Shape>::value, Circle*, Triangle*>::type obj;
        BOOST_CHECK(typeid(obj) == typeid(Triangle*));
    }

    BOOST_AUTO_TEST_CASE(SelectSpecificTypeFromMultipleTypes)
    {
        my::Select<2, int, double, char, std::string> x;
        BOOST_CHECK(typeid(x) == typeid(char));

        estd::Select<6, int, char, double, long int, std::string, short, std::bitset<16>, std::uint64_t>  obj;
        BOOST_CHECK(typeid(obj) == typeid(std::bitset<16>));
    }

BOOST_AUTO_TEST_SUITE_END()