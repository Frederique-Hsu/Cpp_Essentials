/*!
 *  \file       test_resource_management.c++
 *  \brief
 *
 */


#include "test_resource_management.h++"

#include "resource_management.hpp"

#include <cstdlib>

TEST(UTest4FilePtr, CheckFilePtrManagesResource)
{
    FilePtr fptr("new_test.txt", "a+");

    std::string str ="/*!"
                     " *  \\subsection 资源管理"
                     " *"
                     " *  \\details    当函数请求某种资源时，也就是说，当它打开文件、从自由存储中分配一些内存或者一个互斥锁时，系统"
                     " *              常常要求这些资源能在未来某个时刻被正确地释放调。"
                     " *"
                     " *              所谓“正确地释放掉”是指函数应该在返回它的调用者之前释放掉它请求的资源。"
                     " */";

    fptr.write(str);
}

TEST(UTest4FilePtr, GivenFileWhenOpenAndReadExceededStringThenThrowException)
{
    FilePtr fptr("new_test.txt", "r");

    std::string str;
#if false
    try
    {
        str = fptr.read(0xFFFF);
    }
    catch (std::runtime_error& except)
    {
        std::cout << "Catched the exception: " << except.what() << std::endl;
        throw;  // 重新抛出
    }
#else
    EXPECT_THROW({ str = fptr.read(0xFFFF); }, std::runtime_error);
#endif

    std::cout << "The content in this file is: \n" << str << std::endl;
}

TEST(UTest4FinalAction, ExamineFinallyEffect)
{
    int* p = new int{7};
    int* buf = (int*)std::malloc(100 * sizeof(int));

    auto action1 = finally([&]() {
        delete p;
        std::free(buf);

        std::cout << "Goodbye, Cruel world!\n" << std::endl;
    });

    int var = 0;
    std::cout << "var = " << var << std::endl;

    {
        var = 1;
        auto action2 = finally([&]() {
            std::cout << "finally!\n" << std::endl;
            var = 7;
        });
        std::cout << "var = " << var << std::endl;
    }
    std::cout << "var = " << var << std::endl;
}
