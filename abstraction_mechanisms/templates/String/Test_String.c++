/*!
 *  \file       Test_String.c++
 *  \brief      
 *  
 */


#include "String.hpp"

#include <gtest/gtest.h>
#include <map>
#include <iostream>
#include <string>

TEST(UTest4String, InstantiateStringClassTemplate)
{
    String<char> cs;
    String<unsigned char> us;
    
    struct ChineseChar
    {
    };
    
    String<ChineseChar> js;
    EXPECT_EQ(cs.size(), 0);
    
    // String<char> ws = "It's the implementation's job to figure out what code needs to be generated";
    
    std::wstring ws = L"It's the implementation's job to figure out what code needs to be generated";
}

template<typename CharType>
auto countWord()
{
    std::map<String<CharType>, int> word_map;
    for (String<CharType> buff; std::cin >> buff; )
    {
        ++word_map[buff];
    }
    return word_map;
}

namespace std
{
    using string = std::basic_string<char>;
}
       
TEST(UTest4String, CheckTheWordCountingWithStdString)
{
    // GTEST_SKIP();
    
    auto countWordWithStdString = []() {
        std::map<std::string, int> word_map;
        for (std::string buff; std::cin >> buff; )
        {
            ++word_map[buff];
        }
        return word_map;
    };
    
    std::cout << "Please enter the word here: ";
    auto word_map = 
        #if true
            countWordWithStdString();
        #else
            countWord<char>();
        #endif
    for (auto& item : word_map)
    {
        std::cout << item.first << " : " << item.second << std::endl;
    }
}

TEST(UTest4String, CheckSubscriptFunction)
{
    String<char> str("This is a C++ class template");
    
    EXPECT_EQ(str[0], 'T');
    EXPECT_EQ(str[1], 'h');
    
    const char single_const_char = str[5];
    EXPECT_EQ(single_const_char, 'i');
    
    const char& single_char_ref = str[11];
    EXPECT_EQ(single_char_ref, '+');
    
    const String<char> const_str("Constant object");
    EXPECT_EQ(const_str[0], 'C');
    EXPECT_EQ(const_str[1], 'o');
    
    char single_char = const_str[5];
    EXPECT_EQ(single_char, 'a');
    
    const char& const_char_ref = const_str[10];
    EXPECT_EQ(const_char_ref, 'b');
    // const_char_ref = 'X';
}