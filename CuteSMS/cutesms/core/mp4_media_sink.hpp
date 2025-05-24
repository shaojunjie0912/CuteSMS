#pragma once
#include <boost/asio/awaitable.hpp>
#include <functional>
#include <memory>

#include "media_sink.hpp"


namespace cutesms {
class Mp4Segment;
class ThreadWorker;

class Mp4MediaSink : public MediaSink {
public:
    Mp4MediaSink(ThreadWorker *worker);
    virtual ~Mp4MediaSink();
    bool init();
    bool recv_video_init_segment(std::shared_ptr<Mp4Segment> mp4_seg);
    bool recv_audio_init_segment(std::shared_ptr<Mp4Segment> mp4_seg);
    bool recv_video_mp4_segment(std::shared_ptr<Mp4Segment> mp4_seg);
    bool recv_audio_mp4_segment(std::shared_ptr<Mp4Segment> mp4_seg);

    void set_video_init_segment_cb(
        const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> msg)> &cb);
    void set_audio_init_segment_cb(
        const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> msg)> &cb);
    void set_video_mp4_segment_cb(
        const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> msg)> &cb);
    void set_audio_mp4_segment_cb(
        const std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> msg)> &cb);
    void close() override;

private:
    std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> video_init_seg_cb_;
    std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> audio_init_seg_cb_;
    std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> video_seg_cb_;
    std::function<boost::asio::awaitable<bool>(std::shared_ptr<Mp4Segment> seg)> audio_seg_cb_;
};
};  // namespace cutesms