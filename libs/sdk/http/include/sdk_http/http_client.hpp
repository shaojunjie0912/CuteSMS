#pragma once
#include <stdint.h>

#include <base/network/socket_interface.hpp>
#include <boost/asio/awaitable.hpp>
#include <memory>
#include <string>

namespace cutesms {
class ThreadWorker;
class TcpSocket;
class HttpResponse;
class HttpRequest;
class SocketInterface;

class HttpClient : public SocketInterfaceHandler {
public:
    HttpClient(ThreadWorker *worker, bool is_ssl = false);
    virtual ~HttpClient();
    void on_socket_open(std::shared_ptr<SocketInterface> sock) override;
    void on_socket_close(std::shared_ptr<SocketInterface> sock) override;
    void set_buffer_size(size_t s);
    boost::asio::awaitable<std::shared_ptr<HttpResponse>> do_req(const std::string &ip, uint16_t port,
                                                                 const HttpRequest &req);
    void close();

private:
    bool is_ssl_ = false;
    std::shared_ptr<SocketInterface> conn_;
    size_t buffer_size_ = 8 * 1024;
    uint32_t idle_timeout_ = 10000;  // 最大空闲时间(ms)，超过则关闭
};
}  // namespace cutesms