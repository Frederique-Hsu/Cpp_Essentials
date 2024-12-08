/*!
 *  \file       test_mutual_exclusion.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>
#include <functional>
#include <string>

#include "mutual_exclusion.hpp"

TEST(UTester4Mutex, CheckHowMutexWork)
{
    std::thread hello_thrd(hello);
    std::thread world_thrd(world);

    hello_thrd.join();
    world_thrd.join();
}

/*================================================================================================*/

#if 0
static std::recursive_mutex current_count_mutex{};

template<typename Arg, typename... Args>
void writer(Arg a, Args... tail)
{
    current_count_mutex.lock();
    std::cout << a << " ";
    writer(tail...);
    current_count_mutex.unlock();
}

template<typename T>
void writer(T arg)
{
    std::cout << arg << " ";
}

TEST(UTester4Mutex, UseRecursiveMutexToEliminateDeadLock)
{
    std::thread thrd(writer, std::string("Hello"), std::string("World"));
}
#endif

TEST(UTester4Mutex, DISABLED_CheckMutexError)
{
    std::mutex mtx;
    try
    {
        mtx.lock();
        mtx.lock();
    }
    catch (std::system_error& error)
    {
        mtx.unlock();
        std::cout << error.what() << std::endl;
        std::cout << error.code() << std::endl;
    }
}

class Image
{
public:
    Image() {}
};

TEST(UTester4Mutex, CheckTimedMutex)
{
    GTEST_SKIP();

    std::timed_mutex imtx;
    extern Image buf;

    while (true)
    {
        Image next_image;
        // ... computing ....

        if (imtx.try_lock_for(std::chrono::milliseconds(100)))
        {
            buf = next_image;
            imtx.unlock();
            break;
        }
    }
}

void task(std::mutex& m1, std::mutex& m2)
{
    std::unique_lock<std::mutex> lck1(m1);
    std::unique_lock<std::mutex> lck2(m2);

    // do something here...
}

TEST(UTester4Mutex, DISABLED_CheckHowMultipleLocksWork)
{
    std::mutex mtx1;
    std::mutex mtx2;

    std::thread thrd1(task, std::ref(mtx1), std::ref(mtx2));
    std::thread thrd2(task, std::ref(mtx1), std::ref(mtx2));

    thrd1.detach();
    thrd2.detach();
}
