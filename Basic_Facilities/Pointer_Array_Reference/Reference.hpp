/*!
 *  \file       Reference.hpp
 *  \brief      研究C++的引用
 *
 */


#pragma once

#include <utility>
#include <vector>
#include <string>

/*!
 *  \keyword    引用
 *  \details    和指针类似，引用作为对象的别名存放的也是对象的机器地址。与指针对比，引用不会带来额外的开销。
 *
 *  \remark     引用与指针的区别主要包括：
 *  \list
 *              1. 访问引用与访问对象本身从于法形式上看是一样的。
 *              2. 引用所引的永远是一开始初始化的那个对象
 *              3. 不存在“空引用”，引用一定对应着某个对象
 *  \endlist
 *
 *  \note       引用实际上是对象的别名，引用最重要的用途是作为函数的实参或返回值
 *
 *  \list
 *  \annotatedlist  左值引用 lvalue reference : 引用那些我们希望改变值的对象
 *  \annotatedlist  const引用 const referenc : 引用那些我们不希望改变值的对象，比如常量
 *  \annotatedlist  右值引用 rvalue : 所引用对象的值在我们使用之后就无需保留了，比如临时变量
 *  \endlist
 */

#define OLD_STYLE_SWAP          1
#define RVALUE_REF_STYLE_SWAP   2
#define MOVE_STYLE_SWAP         3
#define SWAP                    MOVE_STYLE_SWAP


void increment(int& num);
int next(int p);


/* Class template declaration ====================================================================*/
namespace myspace
{
    template<class K, class V>
    class Map
    {
    public:
        V& operator[](const K& key);

        std::pair<K, V>* begin();
        std::pair<K, V>* end();
    private:
        std::vector<std::pair<K, V>> elem;
    };

    template<class T>
    class vector
    {
    private:
        T* elem;
    public:
        T& operator[](int i);
        const T& operator[](int i) const;

        void push_back(const T& a);
    };

    template<class T> void swap(T& a, T& b);
    template<class T> void swap(T&& a, T& b);
    template<class T> void swap(T& a, T&& b);
}

    void different_type_swap(std::string& s, std::vector<int>& v);

/* Class template implementation =================================================================*/
namespace myspace
{
    template<class K, class V> std::pair<K, V>* Map<K, V>::begin()
    {
        return &elem[0];
    }

    template<class K, class V> std::pair<K, V>* Map<K, V>::end()
    {
        return &elem[0] + elem.size();
    }

    template<class K, class V>
    V& Map<K, V>::operator[](const K& key)
    {
        for (auto& item : elem)
        {
            if (key == item.first)
            {
                return item.second;
            }
        }
        elem.push_back({key, V{}});
        return elem.back().second;
    }

    template<class T> T& vector<T>::operator[](int i)
    {
        return elem[i];
    }

    template<class T> const T& vector<T>::operator[](int i) const
    {
        return elem[i];
    }

#if (SWAP == OLD_STYLE_SWAP)
    template<class T> void swap(T& a, T& b)     // 旧式的swap函数
    {
        T tmp{a};       // 此时，我们拥有了两份a
        a = b;          // 此时，我们也拥有了两份b
        b = tmp;        // 此时，我们拥有了两份tmp
    }
    /*!
     *  \note   右值引用实现了一种“破坏性读取”，某些数据本来需要被拷贝，使用右值引用可以优化其性能。
     *          const左值引用的作用是保护参数内容不被修改。
     *          右值引用所引对象的使用方式与左值引用所引的对象以及普通变量没有什么区别。
     *
     *  \remark 有时程序员明确直到某一对象不再有用了，但是编译器并不知道这一点。如上的swap函数，
     *          如果T是string和vector等拷贝操作非常昂贵的类型，则上面的swap()函数会非常昂贵。
     */
#elif (SWAP == RVALUE_REF_STYLE_SWAP)
    /*！
     *  \note   注意一个事实：其实我们根本没打算拷贝什么东西，我们想要的只是在a, b和tmp之间移动数据而已。
     *          我们可以明确地告诉编译器我们的初衷。
     *
     *          当类型T含有移动构造函数或者移动赋值运算符时， static_cast<T&&>的优化将发挥作用
     */
    template<class T> void swap(T& a, T& b)     // 近乎完美的swap函数
    {
        T tmp{static_cast<T&&>(a)};     // 初始化的同时对a写操作
        a = static_cast<T&&>(b);        // 赋值的同时对b写操作
        b = static_cast<T&&>(tmp);      // 赋值的同时对tmp写操作
    }
#elif (SWAP == MOVE_STYLE_SWAP)
    template<class T> void swap(T& a, T& b)     // 近乎完美的swap函数
    {
        /*!>    \note   std::move(x)等价于static_cast<T&&>(x) */
        T tmp{std::move(a)};    // 从a中移出值
        a = std::move(b);       // 从b中移出值
        b = std::move(tmp);     // 从tmp中移出值
    }
#endif

    template<class T> void swap(T&& a, T& b)
    {
    }

    template<class T> void swap(T& a, T&& b)
    {
        T tmp{std::move(a)};
        a = std::move(b);
        b = std::move(tmp);
    }
}
