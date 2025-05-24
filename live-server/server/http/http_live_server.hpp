#pragma once
#include <functional>
#include <memory>

#include "http_server_base.hpp"

namespace cutesms {
class WebRtcServer;
class HttpLiveServer : public HttpServerBase {
public:
    HttpLiveServer(ThreadWorker *w) : HttpServerBase(w) {}

    virtual ~HttpLiveServer();
    void set_webrtc_server(std::shared_ptr<WebRtcServer> wrtc_server);

private:
    boost::asio::awaitable<void> response_json(std::shared_ptr<HttpResponse> resp, int32_t code,
                                               const std::string &msg);
    bool register_route();

private:
    std::shared_ptr<WebRtcServer> webrtc_server_;
};
};  // namespace cutesms