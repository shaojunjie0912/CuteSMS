#pragma once

#include <boost/asio/awaitable.hpp>
#include <functional>
#include <memory>

#include "http_define.h"
#include "http_request.hpp"

namespace cutesms {
enum HTTP_STATE {
    HTTP_STATE_WAIT_REQUEST_LINE = 0,
    HTTP_STATE_WAIT_HEADER = 1,
    HTTP_STATE_REQUEST_BODY = 2,
    HTTP_STATE_REQUEST_ERROR = 3,
};

class HttpParser {
public:
    boost::asio::awaitable<int32_t> read(const std::string_view& buf);
    void on_http_request(const std::function<boost::asio::awaitable<void>(std::shared_ptr<HttpRequest>)>& cb);
    virtual ~HttpParser();

private:
    std::shared_ptr<HttpRequest> http_req_;
    std::function<boost::asio::awaitable<void>(std::shared_ptr<HttpRequest>)> req_cb_;
    HTTP_STATE state_ = HTTP_STATE_WAIT_REQUEST_LINE;
};

}  // namespace cutesms