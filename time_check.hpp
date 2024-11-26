#ifndef TIME_CHECK_H
#define TIME_CHECK_H

#include <functional>
#include <chrono>
#include <mingw.thread.h> // 包含线程相关的头文件
#include <atomic>
#include <memory>
#include <functional>
#include <mingw.mutex.h> // 包含互斥锁相关的头文件
#include <mingw.condition_variable.h> // 包含条件变量相关的头文件

int waitForInput(Hero *hero, Hero *enemy);

class Timer
{
public:
    Timer() : expired_(true), try_to_expire_(false) // 构造函数，初始化定时器为 expired 状态，未尝试过期
    {
    }

    Timer(const Timer &t) // 拷贝构造函数
    {
        expired_ = t.expired_.load(); // 从被复制的对象中加载 expired 状态
        try_to_expire_ = t.try_to_expire_.load(); // 从被复制的对象中加载尝试过期状态
    }

    ~Timer() // 析构函数
    {
        Expire(); // 调用 Expire 方法确保定时器到期
        // std::cout << "timer destructed!" << std::endl; // 可选输出，显示定时器已被析构
    }

    void StartTimer(int interval, std::function<void()> task) // 启动定时器，周期为 interval 毫秒，执行 task 函数
    {
        if (expired_ == false) // 检查是否已经过期，如果没有，则返回
        {
            // std::cout << "timer is currently running, please expire it first..." << std::endl; // 可选输出，定时器正在运行
            return;
        }
        expired_ = false; // 设置定时器为未过期
        std::thread([this, interval, task]() //创建线程执行定时任务
                    {
            while (!try_to_expire_){ // 如果未尝试过期
                std::this_thread::sleep_for(std::chrono::milliseconds(interval)); // 等待指定时间
                task(); // 执行任务
            }
            // std::cout << "stop task..." << std::endl; // 可选输出，停止任务
            {
                std::lock_guard<std::mutex> locker(mutex_); // 保护变量的互斥锁
                expired_ = true; // 设置为过期状态
                expired_cond_.notify_one(); // 唤醒等待过期的线程
            } })
            .detach(); // 分离线程，让其独立运行
    }

    void Expire() // 过期方法
    {
        if (expired_) // 如果已经过期，则返回
        {
            return;
        }

        if (try_to_expire_) // 如果正在尝试过期，则返回
        {
            // std::cout << "timer is trying to expire, please wait..." << std::endl; // 可选输出，正在尝试过期
            return;
        }
        try_to_expire_ = true; // 设置正在尝试过期状态
        {
            std::unique_lock<std::mutex> locker(mutex_); // 保护变量的唯一锁
            expired_cond_.wait(locker, [this] // 等待直到定时器过期
                               { return expired_ == true; });
            if (expired_ == true) // 如果已经过期
            {
                // std::cout << "timer expired!" << std::endl; // 可选输出，定时器已过期
                try_to_expire_ = false; // 重置尝试过期状态
            }
        }
    }

    template <typename callable, class... arguments>
    void SyncWait(int after, callable &&f, arguments &&...args) // 同步等待指定时间后执行函数
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
        std::this_thread::sleep_for(std::chrono::milliseconds(after)); // 等待指定时间
        task(); // 执行任务
    }

    template <typename callable, class... arguments>
    void AsyncWait(int after, callable &&f, arguments &&...args) // 异步等待指定时间后执行函数
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        std::thread([after, task]() // 创建线程异步执行任务
                    {
            std::this_thread::sleep_for(std::chrono::milliseconds(after)); // 等待指定时间
            task(); // 执行任务
        })
            .detach(); // 分离线程，让其独立运行
    }

        // 异步等待函数
    void AsyncWait(int ms, std::function<void()> func) {
        std::thread([this, ms, func]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            if (!is_stopped) {
                func();
            }
        }).detach();
    }

    // 停止定时器
    void Stop() {
        is_stopped = true;
    }

private:
    std::atomic<bool> expired_; // 过期状态变量
    std::atomic<bool> try_to_expire_; // 尝试过期状态变量
    std::mutex mutex_; // 互斥锁
    std::condition_variable expired_cond_; // 条件变量
    std::atomic<bool> is_stopped{false}; // 用于停止定时器
};



#endif // TIME_CHECK_H