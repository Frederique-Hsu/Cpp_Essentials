/*!
 *  \file       Text.lib.hpp
 *  \brief      organize the Text library.
 *
 */


#pragma once

#include <cstdio>

namespace TextLib
{
class Glyph
{
};

class Word
{
};

class Line
{
};

class Text
{
};

FILE* open(const char*);
void close(FILE* fp);

Word operator+(const Line&, const Line&);
}

#if false
    /*!
     *  \note   glyph()是全局函数，其中的Glyph和Line引用的是全局::Glyph和::Line
     */

    class Glyph
    {
    };

    class Line
    {
    };

    Glyph glyph(Line& ln, int i);
#endif
