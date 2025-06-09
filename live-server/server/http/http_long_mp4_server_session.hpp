#pragma once
#include <boost/asio/experimental/channel.hpp>
#include <boost/asio/experimental/concurrent_channel.hpp>
#include <boost/asio/awaitable.hpp>

#include "core/stream_session.hpp"
#include "base/wait_group.h"
namespace mms {
class HttpRequest;
class HttpResponse;
class Mp4MediaSink;
class ThreadWorker;
class Mp4Segment;

class HttpLongMp4ServerSession : public StreamSession {
public:
    HttpLongMp4ServerSession(std::shared_ptr<HttpRequest> http_req, std::shared_ptr<HttpResponse> http_resp);
    virtual ~HttpLongMp4ServerSession();
    void service();
    void close();
private:
    boost::asio::awaitable<bool> send_fmp4_seg(std::shared_ptr<Mp4Segment> seg);
    boost::asio::experimental::channel<void(boost::system::error_code, std::function<boost::asio::awaitable<bool>()>)> send_funcs_channel_;
    std::shared_ptr<Mp4MediaSink> mp4_media_sink_;
    std::shared_ptr<HttpRequest> http_request_;
    std::shared_ptr<HttpResponse> http_response_;
    WaitGroup wg_;
};
};