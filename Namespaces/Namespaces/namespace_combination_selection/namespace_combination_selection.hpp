/*!
 *  \file       namespace_combination_selection.hpp
 *  \brief
 *
 */


#pragma once

#include <iostream>

namespace his_lib
{
class String
{
};

template<class T> class Vector
{
};
}

namespace her_lib
{
template<class T> class Vector
{
};

class String
{
};
}

namespace my_lib
{
using namespace his_lib;
using namespace her_lib;

using his_lib::String;  // 使用his_lib中的String
using her_lib::Vector;  // 使用her_lib中的Vector，解决潜在的冲突

template<class T> class List
{
};
}

namespace lib2
{
using namespace his_lib;
using namespace her_lib;

using his_lib::String;
using her_lib::Vector;

using her_string = her_lib::String;     // 重命名, using引入别名
template<class T> using his_vector = his_lib::Vector<T>;    // 重命名

template<class T> class List
{
};
}

namespace {
static int a;
void f()
{
    std::cout << "called from unnamed f()" << std::endl;
}
int g()
{
    std::cout << "called from unnamed g()" << std::endl;
    return a;
}
}
