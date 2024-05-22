/*!
 *  \file       test_statements.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>

TEST(ImplicityConversion, CheckEnumerationAsCondition)
{
    enum E1
    {
        a,
        b
    };
    enum class E2
    {
        a,
        b
    };

    auto ConvertEnumeration = [](E1 x, E2 y) -> void
    {
        if (x)  // OK
            std::cout << "Implicitly convert the normal enumeration.\n" << std::endl;
#if false
        if (y)  // error: no conversion to bool
            std::cout << "Cannot implicitly convert the enum class.\n" << std::endl;
#endif
        if (y == E2::a)
            std::cout << "Only allow to compare the enum class variable with its member.\n" << std::endl;
    };

    E1 obj1 = b;
    E2 obj2 = E2::a;
    ConvertEnumeration(obj1, obj2);
}

TEST(ConditionBranchScope, CheckWhetherCanAccessInDifferentBranchScope)
{
    auto fn = [](int i) -> void
    {
        if (i)
        {
            /*!
             *  \warning    A branch of an if-statement cannot be just a declaration.
             *              If we need to introduce a variable name in a branch, it must
             *              be enclosed in a block.
             */
            int x = i + 2;
            ++x;
        }
        else
        {
            // ++x;    // error: x is not in scope
        }
        // ++x;    // error: x is not in scope
    };

    fn(5);
}

TEST(CheckSwitchCaseCandidateItem, CandidateItemMustBeIntOrEnum)
{
    auto fn = [](int i) -> void
    {
        switch (i)
        {
#if false
        case 2.7:
            std::cout << "Error: floating point uses for case" << std::endl;
            break;
#endif
        case 2:
            std::cout << "OK: integer can be used for case" << std::endl;
            break;
#if false
        case 4-2:
            std::cout << "Error: 2 used twice in case labels" << std::endl;
            break;
#endif
        default:
            std::cout << "The rest of candidate items" << std::endl;
            break;
        }
    };

    fn(2);
}
