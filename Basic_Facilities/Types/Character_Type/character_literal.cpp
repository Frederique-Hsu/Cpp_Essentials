/*!
 *  \file       character_literal.cpp
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include <iostream>
#include <cstring>

TEST(UTester4CharacterLiteral, ExpressCharacterInHexOrOctal)
{
    char v1[] = "a\xah\129";
    char v2[] = "a\xah\127";
    char v3[] = "a\xad\127";
    char v4[] = "a\xad\0127";

    std::cout << "v1 = " << v1 << "\nand the length = " << std::strlen(v1) << "\n"
              << "v2 = " << v2 << "\nand the length = " << std::strlen(v2) << "\n"
              << "v3 = " << v3 << "\nand the length = " << std::strlen(v3) << "\n"
              << "v4 = " << v4 << "\nand the length = " << std::strlen(v1) << "\n" << std::endl;

    wchar_t wletter[] = L"ab";
    std::cout << "wletter = " << wletter << std::endl;
}

TEST(UTester4CharacterLiteral, ExpressUnicodeCharacters)
{
    std::cout << "The Unicode string: " << U"\xDEAD" << std::endl;
}


TEST(UTester4CharacterLiteral, ExpressPrefixAndSuffix)
{
    char        single_character_prefix = 'c';
    char16_t    character16_prefix      = u'c';
    char32_t    character32_prefix      = U'c';
    wchar_t     wcharacter_refix        = L'c';

    std::cout << single_character_prefix << "\t"
              << character16_prefix << "\t"
              << character32_prefix << "\t"
              << wcharacter_refix << std::endl;

    char*       str = "mess";
    char*       raw_str_prefix  = R"(\b)";

    using UTF8  = char;
    using UTF16 = char16_t;
    using UTF32 = char32_t;

    UTF8*       utf8_str_prefix  = u8"foo";
    UTF16*      utf16_str_prefix = u"foo";
    UTF32*      utf32_str_prefix = U"foo";
    wchar_t*    wchar_str_prefix = L"foo";

    std::cout << str << "\t"
              << raw_str_prefix << "\t"
              << utf8_str_prefix << "\t"
              << utf16_str_prefix << "\t"
              << utf32_str_prefix << "\t"
              << wchar_str_prefix << "\t"
              << uR"**(foo\(bar))**" << std::endl;
}
