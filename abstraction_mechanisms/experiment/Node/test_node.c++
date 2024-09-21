/*!
 *  \file       test_node.c++
 *  \brief
 *
 */


#include "test_node.h++"


void UTest4Node::SetUp()
{
    m_pnode = create(5);
}

void UTest4Node::TearDown()
{
    destroy(m_pnode);
}

TEST_F(UTest4Node, CheckAppendAndSize)
{
    EXPECT_EQ(size(m_pnode), 1);
    
    append(m_pnode, 12);
    EXPECT_EQ(size(m_pnode), 2);
}

TEST_F(UTest4Node, CheckInsert)
{
    append(m_pnode, 6);
    append(m_pnode, 7);
    append(m_pnode, 8);
    append(m_pnode, 9);
    append(m_pnode, 10);
    
    EXPECT_EQ(size(m_pnode), 6);
    
    Node* node = insert(m_pnode, 3, 25);
    EXPECT_EQ(size(m_pnode), 7);
}