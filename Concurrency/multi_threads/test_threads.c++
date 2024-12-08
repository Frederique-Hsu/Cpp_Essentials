/*!
 *  \file       test_threads.c++
 *  \brief
 *
 */



#include <vector>
#include <thread>
#include <iostream>

#include "threads.hpp"
#include "test_threads.h++"

#if (THREAD_CALLED == THREAD_CALLED_WITH_STATIC_METHOD)
void UTester4MultiThreads::my_task(std::vector<double>& arg)
#elif (THREAD_CALLED == THREAD_CALLED_WITH_BARE_FUNCTION)
void my_task(std::vector<double>& arg)
#endif
{
    std::cout << "This vector contains: ";
    for (auto& elem : arg)
    {
        std::cout << elem << ", ";
    }
    std::cout << "\n" << std::endl;
}

void UTester4MultiThreads::make_test(std::vector<double>& vec)
{
    // std::thread my_thread1(my_task, vec);            // 错误： 传递了vec的拷贝
    /*!
     *  \warning    std::thread arguments must be invocable after conversion to rvalues
     */
    std::thread my_thread2(my_task, std::ref(vec));     // 正确： 以引用方式传递vec
    std::thread my_thread3([&vec](){                    // 正确： 直接采用lambda, 避开了引用问题
        std::vector<double> newvec(vec.begin(), vec.begin() + 5);
        my_task(newvec);
    });

#if 1
    my_thread2.join();
    my_thread3.join();
#else
    /*! \warning    若在子线程使用detach(), 则子线程与主线程分离，运行结果将是错乱的。 */
    my_thread2.detach();
    my_thread3.detach();
#endif
}

TEST_F(UTester4MultiThreads, CheckHowToInstantiateThread)
{
    std::vector<double> numbers{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    make_test(numbers);
}

/* Thread constructing and destructing ===========================================================*/
TEST(ThreadUTester, DISABLED_ConstructThread)
{
    std::vector<std::thread> worker(1000);      // 1000个默认线程

    for (std::size_t index = 0; index != worker.size(); ++index)
    {
        std::thread temp([&index](){
            std::this_thread::sleep_for(std::chrono::microseconds(index));
            std::cout << "current index = " << index << std::endl;
        });
        worker[index] = std::move(temp);
        worker[index].join();
    }
}

void heartbeat()
{
    using namespace std;
    using namespace std::chrono;

    while (true)
    {
        // cout << "Current timestamp " << steady_clock::now().time_since_epoch() << endl;
        this_thread::sleep_for(seconds(1));
    }
}

void tick(int n)
{
    for (int i = 0; i != n; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Alive!" << std::endl;
    }
}

TEST(ThreadUTester, DestructThread)
{
    GTEST_SKIP();
    std::thread timer(tick, 10);
    timer.join();        // join()令主程序等待timer结束
}

TEST(ThreadUTester, DetachThreadToIncurDisaster)
{
    int var = 0;
    std::thread disaster([&](){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        ++var;
        std::cout << "Now current var = " << var << std::endl;
    });
    disaster.detach();
}

/*================================================================================================*/
TEST(ThreadUTester, UseThreadLocalToSuppressDataRace)
{
    std::thread my_task([](){
        Map<std::string, int>::set_default("Heraclides", 1);
    });

    std::thread your_task([](){
        Map<std::string, int>::set_default("Zeno", 2);
    });

    your_task.join();
    my_task.join();

    Map<std::string, int> map_obj;
    auto default_value = map_obj.get_default();
    std::cout << "Now the default value is (" << default_value.first << ", "
              << default_value.second << ").\n" << std::endl;
}
