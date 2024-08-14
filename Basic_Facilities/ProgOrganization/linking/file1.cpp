/*!
 *  \file       file1.cpp
 *  \brief
 *
 */


int x = 1;

int fn()
{
    return int{};
}

static int x1 = 1;      // static表示“不能在其他源文件中访问”，  内部链接

extern const char x2 = 'a';     // const暗示默认内部链接，如果希望x2具有外部链接，则需要在其定义前加上extern


inline int fnct(int i)
{
    return i;
}

extern const int a = 77;

namespace {
    class X
    {
    };

    void f();

    int i;
}
