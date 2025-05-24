#pragma once
#include <memory>

#include "base/thread/thread_pool.hpp"
#include "server_tls/tls_server.hpp"

namespace cutesms {
class TlsSocket;

class RtmpsServer : public SocketInterfaceHandler, public TlsServerNameHandler {
public:
    RtmpsServer(ThreadWorker *w);
    virtual ~RtmpsServer();
    bool start(uint16_t port = 1936);
    void stop();

private:
    std::unique_ptr<TlsServer> tls_server_;
    void on_socket_open(std::shared_ptr<SocketInterface> tls_socket) override;
    void on_socket_close(std::shared_ptr<SocketInterface> tls_socket) override;
    std::shared_ptr<SSL_CTX> on_tls_ext_servername(const std::string &domain_name) override;
};
};  // namespace cutesms