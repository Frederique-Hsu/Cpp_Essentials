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

    b = x.compare_exchange_weak(ref_val, t, std::memory_order_acquire, std::memory_order_consume);

    b = x.compare_exchange_strong(ref_val, t, std::memory_order_acq_rel, std::memory_order_consume);
    EXPECT_EQ(b, true);
    EXPECT_EQ(ref_val, 20);
}

TEST(UTest4AtomicOperation, CheckCompareSwapOperation)
{
    auto fct = [](int value) -> int {
        return value * value;
    };

    std::atomic<int> val = 2;

    int expected = val.load();  // 读取当前值
    int next;
    do 
    {
        next = fct(expected);   // 计算新值
    }
    while (!val.compare_exchange_weak(expected, next));     // 将next写入val或者expected

    EXPECT_EQ(next, 4);
    EXPECT_EQ(expected, 2);
    EXPECT_EQ(val.load(), 4);
}

TEST(UTest4AtomicOperation, AtomicAndMutexWorkTogether)
{
    struct XObj
    {
        int a;
        int b;
    };

    XObj x;
    std::mutex lock_x;
    std::atomic<bool> x_init_flag{false};

    auto doSomething = [&]()
    {
        if (!x_init_flag)
        {
            lock_x.lock();
            if (!x_init_flag)
            {
                x = {.a = 10, .b = 20};
                x_init_flag = true;
            }
            lock_x.unlock();
        }
        std::cout << "Now the x object had changed to {.a = " 
                  << x.a << ", .b = " << x.b << "}" 
                  << std::endl;
    };
}