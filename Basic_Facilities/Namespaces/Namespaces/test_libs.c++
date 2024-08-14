/*!
 *  \file       test_libs.c++
 *  \brief
 *
 */


#include <boost/test/unit_test.hpp>

#include "Graph.lib.hpp"
#include "Text.lib.hpp"

#include <vector>

BOOST_AUTO_TEST_SUITE(UTest4Libraries)

BOOST_AUTO_TEST_CASE(CheckGlyphAndTextLibs)
{
    using namespace GraphLib;
    using namespace TextLib;

    Glyph gl;                   // use the TextLib::Glyph
    std::vector<Shape*> vs;     // use the GraphLib::Shape

    GraphLib::Text txt;

    FILE* fp = TextLib::open("my_precious_data");
    TextLib::close(fp);
}

BOOST_AUTO_TEST_SUITE_END()
