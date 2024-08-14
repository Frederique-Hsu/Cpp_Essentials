/*!
 *  \file       assertion.hpp
 *  \brief
 *
 */


#pragma once

/*!
 *  \subsection     断言
 *
 *  \details        有很多技术可用于检查预置条件和不变式。如果我们希望对检查的原因保持中立，则常使用断言。
 *                  断言是一个逻辑表达时，我们嘉定断言的值为true. 然而断言绝不仅仅是一条注释，我们还需要注明
 *                  一旦它的值为false时应该做什么。
 *
 *  \list       在大量系统中，对于断言和各种各样的需求:
 *
 *      \li     我们需要在编译时断言（由编译器求值）和运行时断言（在运行时求值）中作出选择
 *
 *      \li     对于运行时断言，我们需要选择处理的方式：抛出异常、终止程序还是直接忽略。
 *
 *      \li     除非某些逻辑条件为true, 否则不应生成代码。
 *  \endlist
 *
 *  \list       C++标准提供了两种简单的机制
 *
 *      \li     在<cassert>中，标准库提供了std::assert(A)宏。当且仅当未定义NDEBUG时，它在运行时检查断言A.
 *              一旦断言失败，编译器将输出一条错误信息并终止程序。其中，输出的错误信息包含失败的断言、源文件的名字和行号。
 *
 *      \li     C++语言使用static_assert(A, message)在编译时无条件检查断言A，一旦断言失败，编译器将输出message
 *              以及编译错误信息。
 *  \endlist
 */

#include <string>
#include <stdexcept>

/*!
 *  \section    Prototypes
 */
namespace Assert
{
    enum class Mode
    {
        throw_,
        terminate_,
        ignore_,
    };

    constexpr Mode current_mode = (Mode)CURRENT_MODE;

    constexpr int current_level = CURRENT_LEVEL;

    constexpr int default_level = 1;

    constexpr bool level(int n)
    {
        return n < current_level;
    }

    struct Error : std::runtime_error
    {
        Error(const std::string& str);
    };

    std::string compose(const char* file, const char* function, int line, const std::string& message);

    template<bool condition = level(default_level), class Except = Error>
    void dynamic(bool assertion, const std::string& message = "Assert::dynamic failed");

#if false   // because of multiple definition
    template<> void dynamic<false, Error>(bool, const std::string&)
    {
    }
#endif

    void dynamic(bool b, const std::string& s);

    void dynamic(bool b);
}

/*================================================================================================*/

/*!
 *  \section    Implementations
 */

namespace Assert
{
    template<bool condition, class Except>
    void dynamic(bool assertion, const std::string& message)
    {
        if (assertion)
        {
            return;
        }
        if (current_mode == Mode::throw_)
        {
            throw Except(message);
        }
        if (current_mode == Mode::terminate_)
        {
            std::terminate();
        }
    }
}
