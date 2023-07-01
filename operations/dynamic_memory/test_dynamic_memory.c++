/*!
 *  \file       test_dynamic_memory.c++
 *  \brief
 *
 */


#include "test_dynamic_memory.h++"
#include "manage_pointers.hpp"

#include <complex>
#include <iostream>
#include <numeric>
#include <vector>

TEST_GROUP(UTester4DynamicMemory) {};

TEST(UTester4DynamicMemory, CheckNewOperator)
{
    int* p = new int{7};

    CHECK_TRUE_TEXT(p != nullptr, "Succeeded in allocating dyamic memory for p");
    CHECK_EQUAL(*p, 7);
    delete p;

    auto pc = new std::complex<double>;     // 该复数被初始化为{0.0, 0.0}
    CHECK_EQUAL(pc->real(), 0.0);
    CHECK_EQUAL(pc->imag(), 0.0);
    delete pc;

    auto pi = new int{};    // 该int被初始化为默认值0
    CHECK_EQUAL(*pi, 0);
    delete pi;
}

IGNORE_TEST(UTester4DynamicMemory, CheckObjectPrematureDeletion)
{
    int* p1 = new int{99};
    int* p2 = p1;               // 存在潜在的麻烦
    delete p1;                  // 此时，p2所指的不再是一个有效对象
    p1 = nullptr;               // 造成代码安全的错觉

    char* p3 = new char{'x'};   // 此时，p3有可能指向了p2所指向的内存区域
    *p2 = 999;                  // 该行代码可能会造成麻烦
    std::cout << *p3 << std::endl;      // 输出的内容可能不是x
}

TEST(UTester4DynamicMemory, CheckObjectDoubleDeletion)
{
    int* p = new int[1'000];
    std::cout << "sizeof(p) = " << sizeof(p) << std::endl;

    for (int i = 0; i < 1'000; ++i)
    {
        p[i] = i;
    }
    for (int index = 0; index < 1000; ++index)
    {
        std::cout << *(p + index) << ((index % 10 == 0) ? "\n" : ", ");
    }
    // delete [] p;

    unsigned long long sum = std::accumulate(p, p+1000, 0);
    std::cout << "\nThe sum is " << sum << std::endl;
    delete [] p;
}

TEST(UTester4DynamicMemory, CheckAllocateMemoryForArray)
{
    release_string();
}

/*================================================================================================*/

void TEST_GROUP_CppUTestGroupDetectMemoryLeakageUTester::setup()
{
    MemoryLeakWarningPlugin::saveAndDisableNewDeleteOverloads();
}

void TEST_GROUP_CppUTestGroupDetectMemoryLeakageUTester::teardown()
{
    MemoryLeakWarningPlugin::restoreNewDeleteOverloads();
}

TEST(DetectMemoryLeakageUTester, CheckMemoryLeakage)
{
    try
    {
        leakage(5);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

IGNORE_TEST(DetectMemoryLeakageUTester, CheckMemoryAllocationOverflow)
{
    /*!
     *  \warning    当new发现没有多余的内存可供分配时会发生什么呢？
     *              默认情况下，分配器会抛出一个标准库bad_alloc异常.
     */
    std::vector<char*> vstr;
    try
    {
        while (true)
        {
            char* p = new char[10'000];
            vstr.push_back(p);
            p[0] = 'x';
        }
    }
    catch (std::bad_alloc& exception)
    {
        std::cerr << exception.what() << ", memory exhausted!" << std::endl;
    }
}
