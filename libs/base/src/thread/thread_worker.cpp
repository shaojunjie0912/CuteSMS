#include <sys/prctl.h>

#include <atomic>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/system/error_code.hpp>
#include <functional>
#include <thread>

//
#include <base/thread/thread_worker.hpp>

namespace cutesms {

ThreadWorker::ThreadWorker() : work_guard_(boost::asio::make_work_guard(io_context_)) { running_ = false; }

ThreadWorker::~ThreadWorker() = default;

void ThreadWorker::set_cpu_core(int cpu_core) { cpu_core_ = cpu_core; }

int ThreadWorker::get_cpu_core() { return cpu_core_; }

void ThreadWorker::start() {
    if (running_) {
        return;
    }
    running_ = true;
    thread_ = std::jthread([this]() { work(); });
}

void ThreadWorker::work() {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_core_, &mask);
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
        // print error log
    } else {
    }

    io_context_.run();
}

void ThreadWorker::stop() {
    if (!running_) {
        return;
    }
    running_ = false;
    io_context_.stop();
    work_guard_.reset();
    thread_.join();
}

boost::asio::io_context &ThreadWorker::get_io_context() { return io_context_; }

ThreadWorker::Event::Event(ThreadWorker *worker, const TaskType &f)
    : worker_(worker), f_(f), timer_(worker->get_io_context()) {}

ThreadWorker::Event::~Event() { timer_.cancel(); }

void ThreadWorker::Event::invoke_after(uint32_t ms) {
    timer_.expires_after(std::chrono::milliseconds(ms));
    timer_.async_wait([this](const boost::system::error_code &ec) {
        if (ec != boost::asio::error::operation_aborted) {
            f_(this);
        }
    });
}

ThreadWorker *ThreadWorker::Event::get_worker() { return worker_; }

ThreadWorker::Event *ThreadWorker::create_event(const TaskType &f) {
    Event *ev = new Event(this, f);  // TODO: 内存泄漏?
    return ev;
}

void ThreadWorker::remove_event(Event *ev) {
    dispatch([ev, this]() { delete ev; });
}

}  // namespace cutesms