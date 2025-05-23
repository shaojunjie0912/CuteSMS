#pragma once

#include <atomic>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <functional>
#include <thread>

namespace cutesms {

class ThreadWorker {
public:
    using Task = std::function<void()>;

    ThreadWorker();

    virtual ~ThreadWorker();

    // 设置在哪个 CPU 核心上运行此线程
    void set_cpu_core(int cpu_core);

    // 获取 CPU 核心
    int get_cpu_core();

    // 异步投递任务
    template <typename F, typename... Args>
    void post(F &&f, Args &&...args) {
        boost::asio::post(io_context_, std::bind(f, std::forward<Args>(args)...));
    }

    // 如果当前线程是此线程, 则立即执行, 否则异步投递
    template <typename F, typename... Args>
    void dispatch(F &&f, Args &&...args) {
        boost::asio::dispatch(io_context_, std::bind(f, std::forward<Args>(args)...));
    }

    class Event {
    public:
        Event(ThreadWorker *worker, const std::function<void(Event *ev)> &f);

        ~Event();

    public:
        // 在指定时间后执行回调
        void invoke_after(uint32_t ms);

        // 获取所属的线程
        ThreadWorker *get_worker();

    private:
        ThreadWorker *worker_;               // 事件所属的工作线程
        std::function<void(Event *ev)> f_;   // 事件回调
        boost::asio::deadline_timer timer_;  // 定时器
    };

    // 创建事件
    Event *create_event(const std::function<void(Event *ev)> &f);

    // 移除事件
    void remove_event(Event *ev);

    // 启动线程
    void start();

    // 停止线程
    void stop();

    // 设置 CPU 亲和性并运行 io_context
    void work();

    // 获取 io_context
    boost::asio::io_context &get_io_context();

private:
    int cpu_core_;                        // 指定线程运行的 CPU 核心
    boost::asio::io_context io_context_;  // boost::asio IO 上下文
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
        work_guard_;            // 防止 io_context 在没有工作时退出
    std::jthread thread_;       // 工作线程
    std::atomic_bool running_;  // 线程运行状态标志
};

};  // namespace cutesms