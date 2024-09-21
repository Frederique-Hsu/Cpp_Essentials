/*!
 *  \file       balance_binary_tree.hpp
 *  \brief      
 *  
 */


#pragma once


/*!
 *  \brief      考虑为平衡二叉树涉及一个实验性的平衡策略库。 树会接受一个平衡策略Balancer作为模板类型实参：
 *
 */

template<typename Node, typename Balancer>
struct NodeBase
{
};

/*!
 *  \brief      一个平衡策略就是一个类，提供对树结点的三个操作
 *
 */

struct RedBlackBalancer
{
    template<typename Node> static void add_fixup(Node* node);
    template<typename Node> static void touch(Node* node);
    template<typename Node> static void detach(Node* node);
};


template<typename T> class ForwardIterator;
template<typename T> class DualDirectionalIterator;
template<typename T> class RandomAccessIterator;
