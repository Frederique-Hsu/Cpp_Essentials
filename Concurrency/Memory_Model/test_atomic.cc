/*!
 *  \file       test_atomic.cc
 *  \brief      
 *  
 */


#include <atomic>
#include <gtest/gtest.h>


TEST(UTest4AtomicOperation, CheckHowToApplyAtomic)
{
    std::atomic<int> x{10};
    EXPECT_EQ(x.is_lock_free(), true);

    x.store(20, std::memory_order_relaxed);

    auto t = x.load();
    EXPECT_TRUE(typeid(t) == typeid(int));
    EXPECT_EQ(t, 20);

    int t2 = x.exchange(t, std::memory_order_acquire);
    EXPECT_EQ(t2, 20);
    
    int ref_val;
    auto b = x.compare_exchange_weak(ref_val, t, std::memory_order_consume);
    EXPECT_EQ(b, false);
    EXPECT_EQ(ref_val, 20);
}