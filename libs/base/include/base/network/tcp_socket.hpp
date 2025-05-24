#pragma once

#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>

#include "socket_interface.hpp"

namespace cutesms {

class TcpSocket;
class Session;

class TcpSocket : public SocketInterface {
    friend class TlsSocket;

public:
    TcpSocket(SocketInterfaceHandler *handler, boost::asio::ip::tcp::socket sock, ThreadWorker *worker);
    TcpSocket(SocketInterfaceHandler *handler, ThreadWorker *worker);
    virtual ~TcpSocket();

    void set_socket_inactive_timeout_ms(uint32_t ms);
    virtual boost::asio::awaitable<bool> connect(const std::string &ip, uint16_t port,
                                                 int32_t timeout_ms = 0) override;
    virtual boost::asio::awaitable<bool> send(const uint8_t *data, size_t len,
                                              int32_t timeout_ms = 0) override;
    virtual boost::asio::awaitable<bool> send(std::vector<boost::asio::const_buffer> &bufs,
                                              int32_t timeout_ms = 0) override;
    virtual boost::asio::awaitable<bool> recv(uint8_t *data, size_t len, int32_t timeout_ms = 0) override;
    virtual boost::asio::awaitable<int32_t> recv_some(uint8_t *data, size_t len,
                                                      int32_t timeout_ms = 0) override;
    virtual void open() override;
    virtual void close() override;

    ThreadWorker *get_worker() override { return worker_; }

    bool is_open() { return socket_.is_open(); }

    std::string get_local_address() override;
    std::string get_remote_address() override;

protected:
    uint32_t socket_inactive_timeout_ms_ = 10000;
    ThreadWorker *worker_ = nullptr;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::steady_timer connect_timeout_timer_;
    boost::asio::steady_timer recv_timeout_timer_;
    boost::asio::steady_timer send_timeout_timer_;

    int64_t active_time_ = time(NULL);
    boost::asio::steady_timer active_timeout_timer_;
};
}  // namespace cutesms