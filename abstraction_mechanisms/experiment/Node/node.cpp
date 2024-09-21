/*!
 *  \file       node.cpp
 *  \brief
 *
 */


#include "node.hpp"

#include <stdexcept>


Node* begin(Node* list)
{
    return list;
}

Node* end(Node* list)
{
    return nullptr;
}

Node* operator++(Node node)
{
    Node* pnode = &node;
    pnode = pnode->next;
    return pnode;
}

int operator*(Node node)
{
    return node.data;
}

int sum_elements(Node* first, Node* last)
{
    int sum = int{};
    while (first != last)
    {
        sum += *(*first);
        ++(*first);
    }
    return sum;
}

Node* create(int data)
{
    Node* pnode = new Node{data, nullptr};
    if (pnode == nullptr)
    {
        throw std::bad_alloc{};
    }
    return pnode;
}

void destroy(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    while (node)
    {
        Node* temp_node = node->next;
        delete node;
        node = temp_node;
    }
    node = nullptr;
}

int size(Node* node)
{
    Node* pnode = node;
    int sz = int{0};
    while (pnode)
    {
        ++sz;
        pnode = pnode->next;
    }
    return sz;
}

Node* insert(Node* node, int position, int data)
{
    if ((position < 0) or (position > size(node)))
    {
        throw std::out_of_range("position exceeds the size.");
    }

    Node* pnode = node;
    int index = 0;
    while (pnode)
    {
        index++;
        if (position == index)
        {
            Node* next_node = pnode->next;
            Node* new_node = new Node{data, nullptr};
            pnode->next = new_node;
            new_node->next = next_node;
            return pnode;
        }
        pnode = pnode->next;
    }
    return nullptr;
}

void append(Node* node, int data)
{
    Node* pnode = node;
    while (pnode)
    {
        if (pnode->next == nullptr)
        {
            pnode->next = new Node{data, nullptr};
            return;
        }
        pnode = pnode->next;
    }
}

Node* erase(Node* node, int position)
{
    if (position < 0 or position > size(node))
    {
        throw std::out_of_range("position exceeds the size.");
    }
    
    Node* pnode = node;
    int index = 0;
    while (pnode)
    {
        index++;
        if (position == index-1)
        {
            Node* node_to_delete = pnode->next;
            Node* next_node = node_to_delete->next;
            pnode->next = next_node;
            delete node_to_delete;
            return pnode;            
        }
        pnode = pnode->next;
    }
    return nullptr;
}