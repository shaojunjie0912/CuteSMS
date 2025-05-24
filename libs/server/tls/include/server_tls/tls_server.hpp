#pragma once

#include <base/network/tls_session.hpp>
#include <base/network/tls_socket.hpp>
#include <memory>
#include <server_tcp/tcp_server.hpp>

namespace cutesms {
class TlsServer : public TcpServer, public SocketInterfaceHandler {
public:
    TlsServer(SocketInterfaceHandler *tls_handler, TlsServerNameHandler *name_handler, ThreadWorker *worker);
    virtual ~TlsServer();

public:
    int32_t start_listen(uint16_t port, const std::string &addr = "") override;
    void stop_listen() override;

private:
    void on_socket_open(std::shared_ptr<SocketInterface> tcp_socket) final override;
    void on_socket_close(std::shared_ptr<SocketInterface> tcp_socket) final override;

private:
    bool init_ssl();
    SocketInterfaceHandler *tls_handler_ = nullptr;
    TlsServerNameHandler *server_name_handler_ = nullptr;
};
}  // namespace cutesms