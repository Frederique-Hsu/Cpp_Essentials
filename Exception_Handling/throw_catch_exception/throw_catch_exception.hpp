/*!
 *  \file       throw_catch_exception.hpp
 *  \brief
 *
 */


#pragma once

/*!
 *  \subsection     抛出异常
 *
 *  \brief          我们可以throw任意类型的异常，前提是它能被拷贝和移动
 */


class NoCopy
{
    NoCopy(const NoCopy&) = delete;
};

class MyError
{
};
