
#pragma once
#include <boost/asio/awaitable.hpp>
#include <functional>
#include <list>
#include <memory>
#include <mutex>

#include "spdlog/spdlog.h"

namespace cutesms {
template <typename T>
class ConnPool {
public:
    ConnPool() {}

    virtual ~ConnPool() {}

    boost::asio::awaitable<bool> init(
        uint32_t min_count, uint32_t max_count,
        const std::function<boost::asio::awaitable<std::shared_ptr<T>>()>& allocator) {
        min_count_ = min_count;
        max_count_ = max_count;
        allocator_ = allocator;
        std::lock_guard<std::mutex> lck(mtx_);
        for (uint32_t i = 0; i < min_count; i++) {
            auto c = co_await allocator_();
            if (!c) {
                continue;
            }
            free_conns_.push_back(c);
        }
        co_return true;
    }

    boost::asio::awaitable<std::shared_ptr<T>> get_conn() {
        std::lock_guard<std::mutex> lck(mtx_);
        if (free_conns_.size() <= 0) {
            if (free_conns_.size() + using_conns_.size() < max_count_) {
                auto c = co_await allocator_();
                if (c) {
                    using_conns_.push_back(c);
                }
                co_return c;
            }
            co_return nullptr;
        }
        auto c = free_conns_.front();
        free_conns_.pop_front();
        using_conns_.push_back(c);
        co_return c;
    }

    void recycle_conn(std::shared_ptr<T> c) {
        std::lock_guard<std::mutex> lck(mtx_);
        if (free_conns_.size() + using_conns_.size() > min_count_) {
            auto it = std::find(using_conns_.begin(), using_conns_.end(), c);
            if (it != using_conns_.end()) {
                using_conns_.erase(it);
            }
            return;
        }
        free_conns_.push_back(c);
    }

    void free_conn(std::shared_ptr<T> c) {
        std::lock_guard<std::mutex> lck(mtx_);
        auto it = std::find(using_conns_.begin(), using_conns_.end(), c);
        if (it == using_conns_.end()) {
            return;
        }
        using_conns_.erase(it);
    }

private:
    std::mutex mtx_;
    uint32_t min_count_ = 1;
    uint32_t max_count_ = 2;
    std::function<boost::asio::awaitable<std::shared_ptr<T>>()> allocator_;
    std::list<std::shared_ptr<T>> free_conns_;
    std::list<std::shared_ptr<T>> using_conns_;
};
}  // namespace cutesms