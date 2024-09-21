/*!
 *  \file       test_node.h
 *  \brief      
 *  
 */


#pragma once

#include "node.hpp"

#include <gtest/gtest.h>

class UTest4Node : public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;
protected:
    Node* m_pnode{nullptr};
};
