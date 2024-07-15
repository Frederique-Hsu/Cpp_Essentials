/*!
 *  \file       member_type.hpp
 *  \brief
 *
 */


#pragma once


template<typename T>
class Tree
{
    using value_type = T;

    enum class Policy
    {
        rb,
        splay,
        treeps
    };

    class Node      // nested class
    {
        Node* right;
        Node* left;
        value_type value;

    public:
        void fn(Tree*);
    };

    Node* root;

public:
    void access(Tree::Node* node);
};


/*============================================================================*/

template<typename T>
void Tree<T>::Node::fn(Tree* p)
{
    /*!
     *  \attention  嵌套类可以访问其所属类的成员，甚至是private成员。
     */
    p->root = right;
    value_type v = left->value;
}

template<typename T>
void Tree<T>::access(Tree::Node* node)
{
    /*!
     *  \attention  相反，一个类并没有任何特殊权限能访问其嵌套类的成员。
     */
    // value_type val = right->value;
    value_type v = node->right->value;
    node->fn(this);
}
