/*!
 *  \file       scope.hpp
 *  \brief      研究C++的作用域
 *
 */



#pragma once

#include <vector>
#include <list>
#include <string>

namespace scope
{
    void fn();

    void accessHiddenGlobalVariable();

    void assignLocalVarWithGlobalVar();

    void useSameVariableInStatementScope(std::vector<std::string>& strings,
                                         std::list<int>& numbers);
}
