/*!
 *  \file       test_user_specialization.c++
 *  \brief      
 *  
 */


#include "user_specialization.hpp"
#include "user_specialization.cpp"

#include <iostream>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("Validate the template specialization", "[specialization]")
{
    class Shape
    {
    public:
        virtual ~Shape() = default;
    public:
        virtual void draw() = 0;
    };
    
    struct Node
    {
        int             elem;
        struct Node*    left;
        struct Node*    right;
    };
    
    SECTION("Instantiate the class template Vector<T>")
    {        
        Vector<int> vi;
        Vector<std::string> str_vec;
        Vector<char> chars(10);
        chars[0] = 'H';
        chars[1] = 'e';
        chars[2] = 'l';
        chars[3] = 'l';
        chars[4] = 'o';
        
        CHECK(chars.size() == 10);
    }
    
    SECTION("Instantiate the specialized template Vector<void*>")
    {
        Vector<void*> vpv;
    }
    
    SECTION("Instantiate the partial specialized template Vector<T*>")
    {
        class Circle : public Shape
        {
        public:
            virtual void draw() override
            {
                std::cout << "Circle::draw()" << std::endl;
            }
        };

        class Square : public Shape
        {
        public:
            virtual void draw() override
            {
                std::cout << "Square::draw()" << std::endl;
            }
        };
        
        class Rectangle : public Shape
        {
        public:
            virtual void draw() override
            {
                std::cout << "Rectangle::draw()" << std::endl;
            }
        };
        
        Vector<Shape*> shapes(3);
        shapes[0] = new Circle;
        shapes[1] = new Square;
        shapes[2] = new Rectangle;
        CHECK(shapes.size() == 3);
        
        Vector<Node*> nodes{5};
        nodes[0] = new Node{5, nullptr, nullptr};
        nodes[1] = new Node{3, nullptr, nullptr};
        nodes[2] = new Node{7, nullptr, nullptr};
        nodes[3] = new Node{2, nullptr, nullptr};
        nodes[4] = new Node{4, nullptr, nullptr};
        nodes[0]->left = nodes[1];
        nodes[0]->right = nodes[2];
        nodes[1]->left = nodes[3];
        nodes[1]->right = nodes[4];
        CHECK(nodes.size() == 5);
    }
}