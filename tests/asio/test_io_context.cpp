#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <chrono>  // C++11 时间库
#include <iostream>

void print_hello(const boost::system::error_code& ec) {
    if (ec) {
        std::cerr << "Timer error: " << ec.message() << std::endl;
        return;
    }
    std::cout << "Hello, Asio!" << std::endl;
}

int main() {
    boost::asio::io_context io_ctx;
    boost::asio::steady_timer timer(io_ctx, std::chrono::seconds(2));  // 创建一个2秒后触发的定时器

    // 发起异步等待
    // print_hello 将在2秒后被 io_ctx 的某个线程调用
    timer.async_wait(&print_hello);

    std::cout << "Timer started, waiting for 2 seconds..." << std::endl;

    // 必须调用 run() 来处理异步事件
    io_ctx.run();

    return 0;
}