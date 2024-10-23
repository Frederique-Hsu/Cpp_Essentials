/*!
 *  \file       nodes.hpp
 *  \brief      
 *  
 */


#pragma once

template<typename T>
struct Balance
{
    bool compare(const T& a, const T& b);
};

template<typename T, typename Balance>
struct NodeBase : Balance
{
    T*  left_child;
    T*  right_child;

    NodeBase();

    void insert(T& t);
};

template<typename ValType, typename Balance>
struct Node : NodeBase<Node<ValType, Balance>, Balance>
{
    ValType m_value;
    Node(ValType value);
};

template<typename ValType, typename Balance>
struct SearchNode : public NodeBase<SearchNode<ValType, Balance>, Balance>
{
    ValType m_val;
    SearchNode(ValType val);
};


#include "nodes_impl.hpp"