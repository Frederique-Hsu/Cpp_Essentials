/*!
 *  \file       JoiningThread
 *  \brief
 *
 */


#pragma once

#include <thread>


class JoiningThread
{
private:
    std::thread m_thrd;

public:
    JoiningThread() noexcept = default;
    template<typename Callable, typename...  Args> explicit JoiningThread(Callable&& func, Args&&... args);
    explicit JoiningThread(std::thread thrd) noexcept;
    JoiningThread(JoiningThread&& other) noexcept;
    JoiningThread& operator=(JoiningThread&& other) noexcept;
    JoiningThread& operator=(std::thread other) noexcept;
    ~JoiningThread() noexcept;

public:
    void swap(JoiningThread& other) noexcept;
    bool joinable() const noexcept;
    void join();
    void detach();
    std::thread::id get_id() const noexcept;
    std::thread& as_thread() noexcept;
    const std::thread& as_thread() const noexcept;
};




template<typename Callable, typename... Args>
JoiningThread::JoiningThread(Callable&& func, Args&&... args)
    : m_thrd(std::forward<Callable>(func), std::forward<Args>(args)...)
{
}
