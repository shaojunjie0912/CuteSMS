#include <protocol_http/http_define.h>
#include <spdlog/spdlog.h>

#include <base/network/tcp_socket.hpp>
#include <base/network/tls_socket.hpp>
#include <protocol_http/http_request.hpp>
#include <protocol_http/http_response.hpp>
#include <sdk_http/http_client.hpp>

namespace cutesms {
HttpClient::HttpClient(ThreadWorker *worker, bool is_ssl) : is_ssl_(is_ssl) {
    if (is_ssl) {
        conn_ = std::make_shared<TlsSocket>(this, worker);
    } else {
        conn_ = std::make_shared<TcpSocket>(this, worker);
    }
}

HttpClient::~HttpClient() {}

void HttpClient::on_socket_open(std::shared_ptr<SocketInterface> sock) {
    ((void)(sock));
    return;
}

void HttpClient::on_socket_close(std::shared_ptr<SocketInterface> sock) {
    ((void)(sock));
    return;
}

void HttpClient::set_buffer_size(size_t s) { buffer_size_ = s; }

boost::asio::awaitable<std::shared_ptr<HttpResponse>> HttpClient::do_req(const std::string &ip, uint16_t port,
                                                                         const HttpRequest &req) {
    bool ret = co_await conn_->connect(ip, port);
    if (!ret) {
        co_return nullptr;
    }

    std::string req_data = req.to_req_string();
    if (!co_await conn_->send((const uint8_t *)req_data.data(), req_data.size())) {
        co_return nullptr;
    }

    std::shared_ptr<HttpResponse> resp = std::make_shared<HttpResponse>(conn_, buffer_size_);
    co_return resp;
}

void HttpClient::close() {
    if (conn_) {
        conn_->close();
    }
}
}  // namespace cutesms