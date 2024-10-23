/*!
 *  \file       nodes_impl.hpp
 *  \brief      
 *  
 */


template<typename T, typename Balance>
NodeBase<T, Balance>::NodeBase() : Balance(), left_child{nullptr}, right_child{nullptr}
{
}

template<typename T, typename Balance>
void NodeBase<T, Balance>::insert(T& t)
{
    if (this->compare(t, left_child))
    {
        // ... insert the new node into the left child of tree node
    }
    else
    {
        // ... insert the new node into the right child of tree node
    }
}

template<typename ValType, typename Balance>
Node<ValType, Balance>::Node(ValType value) : NodeBase<Node<ValType, Balance>, Balance>(), m_value{value}
{
}