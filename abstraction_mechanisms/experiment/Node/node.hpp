/*!
 *  \file       node.hpp
 *  \brief      
 *  
 */


#pragma once


typedef struct Node
{
    int             data;
    struct Node*    next;
}
Node, *PNode;

Node* create(int data);
void destroy(Node* node);
void append(Node* node, int data);
Node* insert(Node* node, int position, int data);
Node* erase(Node* node, int position);
int size(Node* node);
int get(Node* node, int position);
void set(Node* node, int position, int data);
Node* find(Node* node, int data);
void print(Node* node);
Node* operator++(Node node);
int operator*(Node node);
Node* begin(Node* list);
Node* end(Node* list);

int sum_elements(Node* first, Node* last);