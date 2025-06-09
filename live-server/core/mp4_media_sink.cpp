#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

#include "mp4_media_sink.hpp"
#include "mp4_media_source.hpp"

#include "base/thread/thread_worker.hpp"
using namespace mms;
Mp4MediaSink::Mp4MediaSink(ThreadWorker *worker) : MediaSink(worker) {

}

Mp4MediaSink::~Mp4MediaSink() {

}

bool Mp4MediaSink::init() {
    return true;
}

void Mp4MediaSink::close() {
    video_seg_cb_ = {};
    audio_seg_cb_ = {};
    audio_init_seg_cb_ = {};
    audio_init_seg_cb_ = {};
    return;
}

bool Mp4MediaSink::recv_video_init_segment(std::shared_ptr<Mp4Segment> mp4_seg) {
    auto self(this->shared_from_this());
    boost::asio::co_spawn(worker_->get_io_context(), [this, self, mp4_seg]()->boost::asio::awaitable<void> {
        co_await video_init_seg_cb_(mp4_seg);
        co_return;
    }, boost::asio::detached);
    return true;
}

bool Mp4MediaSink::recv_audio_init_segment(std::shared_ptr<Mp4Segment> mp4_seg) {
    auto self(this->shared_from_this());
    boost::asio::co_spawn(worker_->get_io_context(), [this, self, mp4_seg]()->boost::asio::awaitable<void> {
        co_await audio_init_seg_cb_(mp4_seg);
        co_return;
    }, boost::asio::detached);
    return true;
}

bool Mp4MediaSink::recv_video_mp4_segment(std::shared_ptr<Mp4Segment> mp4_seg) {
    auto self(this->shared_from_this());
    boost::asio::co_spawn(worker_->get_io_context(), [this, self, mp4_seg]()->boost::asio::awaitable<void> {
        co_await video_seg_cb_(mp4_seg);
        co_return;
    }, boost::asio::detached);
    return true;
}

bool Mp4MediaSink::recv_audio_mp4_segment(std::shared_ptr<Mp4Segment> mp4_seg) {
    auto self(this->shared_from_this());
    boost::asio::co_spawn(worker_->get_io_context(), [this, self, mp4_seg]()->boost::asio::awaitable<void> {
        co_await audio_seg_cb_(mp4_seg);
        co_return;
    }, boost::asio::detached);
    return true;
}

void Mp4MediaSink::set_video_init_segment_cb(const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> & cb) {
    video_init_seg_cb_ = cb;
}

void Mp4MediaSink::set_audio_init_segment_cb(const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> & cb) {
    audio_init_seg_cb_ = cb;
}

void Mp4MediaSink::set_video_mp4_segment_cb(const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> & cb) {
    video_seg_cb_ = cb;
}

void Mp4MediaSink::set_audio_mp4_segment_cb(const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> & cb) {
    audio_seg_cb_ = cb;
}
