#pragma once
#include <atomic>
#include <memory>

#include <boost/asio/steady_timer.hpp>

#include "../media_bridge.hpp"
#include "base/wait_group.h"

namespace mms {
class PublishApp;
class Mp4MediaSink;
class ThreadWorker;
class MpdLiveMediaSource;

class Mp4ToMpd : public MediaBridge {
public:
    Mp4ToMpd(ThreadWorker *worker, std::shared_ptr<PublishApp> app, std::weak_ptr<MediaSource> origin_source, const std::string & domain_name, const std::string & app_name, const std::string & stream_name);
    virtual ~Mp4ToMpd();
    bool init() override;
    void close() override;
private:
    std::shared_ptr<Mp4MediaSink> mp4_media_sink_;
    std::shared_ptr<MpdLiveMediaSource> mpd_media_source_;

    boost::asio::steady_timer check_closable_timer_;

    WaitGroup wg_;
};
};