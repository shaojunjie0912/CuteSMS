#pragma once
#include <atomic>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/experimental/concurrent_channel.hpp>
#include <boost/system/error_code.hpp>
#include <functional>
#include <memory>

#include "base/wait_group.h"


namespace cutesms {
class MediaSource;
class MediaEvent;
class ThreadWorker;

class MediaSink : public std::enable_shared_from_this<MediaSink> {
    friend class MediaSource;

public:
    MediaSink(ThreadWorker *worker);
    virtual ~MediaSink();
    ThreadWorker *get_worker();

    void set_source(std::shared_ptr<MediaSource> source);
    std::shared_ptr<MediaSource> get_source();

    virtual void close();
    void on_close(const std::function<void()> &close_cb);

    void set_event_cb(const std::function<void(const MediaEvent &ev)> &ev_cb);
    void recv_event(const MediaEvent &ev);

protected:
    std::shared_ptr<MediaSource> source_{nullptr};
    ThreadWorker *worker_;
    bool working_ = false;

    std::function<void()> close_cb_;
    std::function<void(const MediaEvent &ev)> ev_cb_;
};

class LazyMediaSink : public MediaSink {
public:
    LazyMediaSink(ThreadWorker *worker);
    virtual ~LazyMediaSink();
    virtual void wakeup();
    virtual boost::asio::awaitable<void> do_work() = 0;
    virtual void close() override;

protected:
    std::atomic<bool> closing_{false};
    WaitGroup wg_;
};

};  // namespace cutesms