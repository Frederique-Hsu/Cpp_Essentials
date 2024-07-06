/*!
 *  \file       namespace_for_versioning.hpp
 *  \brief      Utilize the namespace to control the version selection.
 *
 */


#pragma once

/*!
 *  \note   C++提供了一种在多个不同版本间进行选择的机制，可以简单明确地保证用户只看到其中一个特定版本。
 *          这就是内联名字空间 inline namespace
 */

namespace Popular
{
    inline namespace V3_2       // V3_2提供了Popular的默认含义
    {
        double fn(double);
        int fn(int);
        template<class T> class C
        {
        };
    }

    namespace V3_0
    {
        double fn(double);
    }

    namespace V2_4_2
    {
        double fn(double);
        template<class T> class C
        {
        };
    }
}
