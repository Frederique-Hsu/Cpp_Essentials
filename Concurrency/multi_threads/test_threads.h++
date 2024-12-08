/*!
 *  \file       test_threads.h++
 *  \brief
 *
 */


#pragma once

#include <gtest/gtest.h>

#define THREAD_CALLED_WITH_STATIC_METHOD    1
#define THREAD_CALLED_WITH_BARE_FUNCTION    2
#define THREAD_CALLED                       THREAD_CALLED_WITH_STATIC_METHOD

class UTester4MultiThreads : public ::testing::Test
{
public:
#if (THREAD_CALLED == THREAD_CALLED_WITH_STATIC_METHOD)
    /*!
     *  \warning    Reference to non-static member function must be called.
     *              So, here must add the `static`
     */
    static void my_task(std::vector<double>& arg);
#endif
    void make_test(std::vector<double>& vec);
};

#if (THREAD_CALLED == THREAD_CALLED_WITH_BARE_FUNCTION)
    void my_task(std::vector<double>& arg);
#endif
