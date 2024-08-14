/*!
 *  \file       exception.cpp
 *  \brief
 *
 */


#include "exception.hpp"

#include <limits>
#include <cstring>


void fn(int n)
{
    if (n < 0 || n > std::numeric_limits<int>::max())
    {
        throw RangeError{};
    }
}

/*!
 *  \note   可以把异常处理机制当成一种新的控制结构，它的任务是向调用者返回某个值。
 *          如下的二叉搜索树的例子，则是利用异常捕获来返回搜索结果的。
 */
void fnd(Tree* p, const std::string& s)
{
    if (s == p->str)
    {
        throw p;
    }
    if (p->left)
    {
        fnd(p->left, s);
    }
    if (p->right)
    {
        fnd(p->right, s);
    }
}

Tree* find(Tree* p, const std::string& s)
{
    try
    {
        fnd(p, s);
    }
    catch (Tree* q)
    {
        return q;
    }
    return nullptr;
}

void init(Tree* p, const std::string& s)
{
    p->str = s;
    p->left = nullptr;
    p->right = nullptr;
}

void insert(Tree* p, const std::string& s)
{
    if (p == nullptr)
    {
        p = new Tree;
        p->str = s;
        p->left = nullptr;
        p->right = nullptr;
    }
    if (std::strcmp(p->str.c_str(), s.c_str()) < 0)
    {
        insert(p->left, s);
    }
    else if (std::strcmp(p->str.c_str(), s.c_str()) > 0)
    {
        insert(p->right, s);
    }
    else if (std::strcmp(p->str.c_str(), s.c_str()) == 0)
    {
        ; // do nothing
    }
}

void deinit(Tree* p)
{
    if (p->left)
    {
        deinit(p->left);
    }
    if (p->right)
    {
        deinit(p->right);
    }
    delete p;
}
