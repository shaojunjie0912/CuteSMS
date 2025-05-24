#include <array>
#include <atomic>
#include <memory>

#include "base/network/session.hpp"

namespace cutesms {
class WebSocketPacket;
class SocketInterface;

class WebSocketServerSession : public Session {
public:
    WebSocketServerSession(std::shared_ptr<SocketInterface> sock);
    virtual ~WebSocketServerSession();
    void service() override;
    void close() override;

private:
    std::shared_ptr<SocketInterface> sock_;
    std::shared_ptr<WebSocketPacket> packet_;
};
};  // namespace cutesms