#ifndef TIME_CHECK_H
#define TIME_CHECK_H

#include <functional>
#include <chrono>
#include <mingw.thread.h> // 包含线程相关的头文件
#include <atomic>
#include <memory>
#include <functional>
#include <mingw.mutex.h>              // 包含互斥锁相关的头文件
#include <mingw.condition_variable.h> // 包含条件变量相关的头文件

int waitForInput(Hero *hero, Hero *enemy);

class Timer
{
public:
    // 定时器构造时接受一个钩子函数
    Timer(std::function<void()> timeout_callback)
        : timeout_callback(timeout_callback), is_stopped(false) {}

    // 异步等待函数，等待时间到后调用钩子函数
    void AsyncWait(int ms)
    {
        std::thread([this, ms]()
                    {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            if (!is_stopped) {
                timeout_callback(); // 超时后调用钩子函数
                timeout_triggered = true; // Set flag indicating timeout
            } })
            .detach();
    }

    // 停止定时器
    void Stop()
    {
        is_stopped = true;
    }

    bool IsTimeoutTriggered() const
    {
        return timeout_triggered;
    }

private:
    std::function<void()> timeout_callback; // 钩子函数
    bool is_stopped;                        // 标记定时器是否已停止
    std::atomic<bool> timeout_triggered;
};

#endif // TIME_CHECK_H