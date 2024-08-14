/*!
 *  \file       test_exception.c++
 *  \brief
 *
 */


#include "exception.hpp"

#include <gtest/gtest.h>

TEST(UTest4Exception, DISABLED_CheckTreeSearchException)
{
    Tree* tree = new Tree;

    init(tree, "hello");
    insert(tree, "world");
    insert(tree, "C++");
    insert(tree, "programming");
    insert(tree, "object");
    insert(tree, "oriented");

    Tree* t = find(tree, "object");
    EXPECT_STREQ(t->str.c_str(), "object");

    deinit(tree);
}
