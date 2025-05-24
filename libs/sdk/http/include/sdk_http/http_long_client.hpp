#pragma once

#include <protocol_http/http_define.h>
#include <stdint.h>

#include <base/network/tcp_socket.hpp>
#include <protocol_http/http_request.hpp>
#include <protocol_http/http_response.hpp>
#include <string>

namespace cutesms {
class ThreadWorker;

class HttpLongClient : public TcpSocket, public SocketInterfaceHandler {
public:
    HttpLongClient(ThreadWorker *worker) : TcpSocket(this, worker) {}

    virtual ~HttpLongClient() {}

    void on_socket_open(std::shared_ptr<SocketInterface> sock) {
        ((void)sock);
        return;
    }

    void on_socket_close(std::shared_ptr<SocketInterface> sock) {
        ((void)sock);
        return;
    }

public:
    boost::asio::awaitable<std::shared_ptr<HttpResponse>> do_req(const HttpRequest &req) {
        std::string req_data = req.to_req_string();
        if (!co_await send((const uint8_t *)req_data.data(), req_data.size())) {
            co_return nullptr;
        }
        std::shared_ptr<HttpResponse> resp = std::make_shared<HttpResponse>(shared_from_this());
        co_return resp;
    }

private:
    uint32_t idle_timeout_ = 10000;  // 最大空闲时间(ms)，超过则关闭
};
}  // namespace cutesms