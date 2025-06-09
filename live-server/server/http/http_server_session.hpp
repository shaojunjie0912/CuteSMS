/*
 * @Author: jbl19860422
 * @Date: 2023-09-16 10:32:17
 * @LastEditTime: 2023-12-27 21:23:40
 * @LastEditors: jbl19860422
 * @Description: 
 * @FilePath: \mms\mms\server\http\http_server_session.hpp
 * Copyright (c) 2023 by jbl19860422@gitee.com, All Rights Reserved. 
 */
#pragma once
#include <memory>
#include <atomic>
#include <array>
#include <list>

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/redirect_error.hpp>

#include "protocol/http/http_parser.hpp"
#include "protocol/http/http_define.h"
#include "protocol/http/http_request.hpp"
#include "server/session.hpp"
#include "core/rtmp_media_sink.hpp"
#include "protocol/http/http_response.hpp"
#include "websocket_server_session.hpp"
#include "log/log.h"
#include "base/wait_group.h"

namespace mms {
class HttpServerSession;
class SocketInterface;

class HttpRequestHandler {
public:
    virtual boost::asio::awaitable<bool> on_new_request(std::shared_ptr<HttpServerSession> session, 
                                                        std::shared_ptr<HttpRequest> req, 
                                                        std::shared_ptr<HttpResponse> resp) = 0;
};

class HttpServerSession : public Session {
public:
    HttpServerSession(HttpRequestHandler *request_handler, std::shared_ptr<SocketInterface> sock);
    virtual ~HttpServerSession();
    std::shared_ptr<SocketInterface> get_sock();

    void service() override;
    void close() override;

    boost::asio::awaitable<void> on_http_request(std::shared_ptr<HttpRequest> req);
    boost::asio::awaitable<void> process_one_req(std::shared_ptr<HttpRequest> req);
    boost::asio::awaitable<void> close_or_do_next_req();
protected:
    boost::asio::awaitable<void> cycle_recv();
    boost::asio::awaitable<std::pair<bool,int32_t>> parse_recv_buf(const char *buf, int32_t len);
    bool is_websocket_req(std::shared_ptr<HttpRequest> req);
protected:
    HttpRequestHandler *request_handler_;
    std::shared_ptr<SocketInterface> sock_;
    HttpParser http_parser_;
    std::shared_ptr<HttpRequest> curr_req_;
    std::list<std::shared_ptr<HttpRequest>> reqs_;
    bool is_websocket_ = false;
protected:
    std::unique_ptr<char[]> buf_;
    int32_t buf_size_ = 0;
    int32_t buf_pos_ = 0;
    WaitGroup wg_;
};

};