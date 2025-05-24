#pragma once
#include <base/network/session.hpp>
#include <memory>

namespace cutesms {

class TcpSocket;
class TlsSocketHandler;
class TlsServerNameHandler;
class SocketInterfaceHandler;

class TlsSession : public Session {
public:
    TlsSession(bool mode, SocketInterfaceHandler *tls_handler, TlsServerNameHandler *server_name_handler,
               std::shared_ptr<TcpSocket> tcp_socket);

    virtual ~TlsSession();

    std::shared_ptr<TcpSocket> get_tcp_socket();

    void service() override;
    void close() override;

protected:
    SocketInterfaceHandler *tls_socket_handler_ = nullptr;
    TlsServerNameHandler *server_name_handler_ = nullptr;
    std::shared_ptr<TcpSocket> tcp_socket_;
    bool is_server_mode_;
};
}  // namespace cutesms