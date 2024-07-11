/*!
 *  \file       common.hpp
 *  \brief
 *
 */


#pragma once

void gn();

/*!
 *  \subsection     头文件
 *
 *  \details        一般原则是，头文件可包含：
 *
 *  \list
 *      \li         具名的名字空间               namespace N {  ...  }
 *      \li         inline名字空间              inline namespace N { ... }
 *      \li         类型定义                    struct Point { int x; int y; };
 *      \li         模板声明                    template<typename T> class Z;
 *      \li         模板定义                    template<typename T> class V { ... };
 *      \li         函数声明                    extern int strlen(const char*);
 *      \li         inline函数定义              inline char get(char* p) { ... }
 *      \li         constexpr函数定义           constexpr int fac(int n) { return (n < 2) ? 1 : n*fac(n-1); }
 *      \li         数据声明                    extern int a;
 *      \li         const定义                  const float pi = 3.1415926;
 *      \li         constexpr定义              constexpr float pi2 = pi * pi;
 *      \li         枚举                       enum class Light { red, yellow, green };
 *      \li         名字声明                    class Matrix;
 *      \li         类型别名                    using value_type = long;
 *      \li         编译时断言                   static_assert(4 <= sizeof(int), "small ints");
 *      \li         包含指令                    #include <algorithm>
 *      \li         宏定义                      #define VERSION 12.03
 *      \li         条件编译指令                 #ifdef __cplusplus
 *  \endlist
 *
 *  \note           头文件中不应该包含：
 *  \list
 *      \li         普通函数定义                 char get(char* p) { return *p++; }
 *      \li         数据定义                    int a;
 *      \li         集合定义                    short tbl[] = { 1, 2, 3 };
 *      \li         无名名字空间                 namespace { int b; }
 *      \li         using指示                   using namespace std;
 *  \endlist
 */
