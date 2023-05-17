/*!
 *  \file       Reference.hpp
 *  \brief      研究C++的引用
 *
 */


#pragma once

#include <utility>
#include <vector>

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


void increment(int& num);
int next(int p);

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
