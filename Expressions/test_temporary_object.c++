/*!
 *  \file       test_temporary_object.c++
 *  \brief
 *
 */


#include "test_temporary_object.h++"

#include <iostream>
#include <string>
#include <cstring>



void TEST_GROUP_CppUTestGroupUTester4TemporaryObject::foo(std::string& s1, std::string& s2, std::string& s3)
{
    const char* cs = (s1 + s2).c_str();
    /*!
     *  \warning    上述表达数 s1 + s2 是临时对象，在表达式末尾，该临时对象会被销毁。
     *              当临时对象被销毁后，无法确保一定会退出该部分区域。因此，cs可能会指向一片已被释放的存储空间，
     *              而输出操作 cout << cs 是否能正常工作就完全看运气。
     *              编译器能检测并报告很多类似的错误。
     */
    std::cout << cs << std::endl;

    auto len = std::strlen(cs = (s2 + s3).c_str());
    std::cout << "len = " << len << std::endl;

    if ((std::strlen(cs = (s2 + s3).c_str()) < 8) or (cs[0] == 'o'))
    {
        std::cout << cs << std::endl;
    }
}

void TEST_GROUP_CppUTestGroupUTester4TemporaryObject::bar(std::string& s1, std::string& s2, std::string& s3)
{
    std::cout << s1 + s2 << std::endl;
    std::string s = s2 + s3;
    if ((s.length() > 8) and (s[0] == 'o'))
    {
        std::cout << s << std::endl;
    }
}

void TEST_GROUP_CppUTestGroupUTester4TemporaryObject::tor(std::string& s1, std::string& s2)
{
    const std::string& s = s1 + s2;     // 临时对象可以用作const引用的初始化器
    std::string ss = s1 + s2;           // 临时对象用作命名对象的初始化器
    /*!
     *  \remark     销毁临时对象的方式与销毁隐式生成的临时变量的方式完全一致。
     */

    // std::string& tmp = s1 + s2;     // 错误： 不能把一个临时对象 s1 + s2 绑定到非const左值引用上。

    std::cout << "s = " << s << std::endl;
    std::cout << "ss = " << ss << std::endl;
}

TEST(UTester4TemporaryObject, CheckTemporaryObjectIsValid)
{
    std::string temporary("temporary "), object(" object "), is_valid("is valid?");
    foo(temporary, object, is_valid);
    bar(temporary, object, is_valid);
    tor(temporary, object);
}
