/*!
 *  \file       atomic.cpp
 *  \brief
 *
 */



#include "atomic.hpp"

enum memory_order
{
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
};

#if 0
/*!
 *  \remark     为了能在采用放松内存模型的架构上实现显著优化，C++标准提供了一个属性[[carries_dependency]]
 *              可跨越函数调用传递内存依赖性
 */
[[carries_dependency]] struct foo* fn(int i)
{
    return foo_head[i].load(std::memory_order_consume);
}
#endif
