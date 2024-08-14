/*!
 *  \file       test_namespace_for_versioning.c++
 *  \brief
 *
 */


#include "namespace_for_versioning.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(UTest4NamespaceForVersioning)

BOOST_AUTO_TEST_CASE(CheckWhetherInlineNamespaceCanSelectDifferentVersion)
{
    using namespace Popular;

    auto test = []() {
        /*!
         *  \attention  通过将inline加在不同版本的namespace之前，就可以为fn(的double)选择不同的版本。
         *              这对于控制library的版本非常有帮助，可以非常方便地选择与替换不同的版本。
         */
        fn(1);
        V3_0::fn(1);
        V2_4_2::fn(1);
    };

    test();
}

BOOST_AUTO_TEST_SUITE_END()
