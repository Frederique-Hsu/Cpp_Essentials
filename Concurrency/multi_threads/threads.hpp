/*!
 *  \file       threads.hpp
 *  \brief
 *
 */


#pragma once

#include <thread>

struct guarded_thread : std::thread
{
    using std::thread::thread;
    ~guarded_thread()
    {
        if (thrd.joinable())
            thrd.join();
    }
private:
    std::thread thrd;
};


/*!
 *  \note   On all major implementations `threads` are preemptable; that is, the implementation
 *          can switch from one task to another to ensure that all `threads` progress at a
 *          reasonable rate. However, for historical and language technical reasons, preemption
 *          is only encouraged rather than required by the standard.
 */


template<typename K, typename V>
class Map
{
public:
    Map();
private:
    static thread_local std::pair<K, V> default_value;
public:
    static void set_default(const K&, V);
    std::pair<K, V>& get_default() const;
};


/* Implementation ================================================================================*/
template<typename K, typename V> Map<K, V>::Map()
{
}

template<typename K, typename V>
thread_local std::pair<K, V> Map<K, V>::default_value{K{}, V{}};

template<typename K, typename V>
void Map<K, V>::set_default(const K& key, V value)
{
    default_value = std::pair<K, V>(key, value);
}

template<typename K, typename V>
std::pair<K, V>& Map<K, V>::get_default() const
{
    return default_value;
}
