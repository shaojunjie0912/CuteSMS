#pragma once

#include <stdint.h>

#include <base/network/udp_socket.hpp>
#include <boost/array.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/spawn.hpp>
#include <string>
#include <vector>

namespace cutesms {
#define MAX_UDP_RECV_BUF 2 * 1024 * 1024
class ThreadWorker;
class UdpSocket;

class UdpServer : public UdpSocketHandler {
public:
    UdpServer(const std::vector<ThreadWorker*>& workers);
    virtual ~UdpServer();
    bool start_listen(const std::string& ip, uint16_t port);
    void stop_listen();

protected:
    uint16_t port_;
    std::vector<ThreadWorker*> workers_;
    std::vector<UdpSocket*> udp_socks_;
    std::vector<boost::array<uint8_t, MAX_UDP_RECV_BUF>> recv_bufs_;
    bool running_ = false;
};
}  // namespace cutesms