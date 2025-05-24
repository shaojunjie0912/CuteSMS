#pragma once
#include <cstdint>
#include <memory>
#include <protocol_rtmp/rtmp_define.hpp>


namespace cutesms {
class RtmpWindowAckSizeMessage {
public:
    RtmpWindowAckSizeMessage(uint32_t size) : ack_window_size_(size) {}

    uint32_t size() { return 0; }

    int32_t decode(std::shared_ptr<RtmpMessage> rtmp_msg);
    std::shared_ptr<RtmpMessage> encode() const;

private:
    uint32_t ack_window_size_ = 0;
};
}  // namespace cutesms