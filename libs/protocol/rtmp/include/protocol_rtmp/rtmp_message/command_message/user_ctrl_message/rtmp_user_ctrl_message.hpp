#pragma once
#include <protocol_rtmp/rtmp_define.hpp>

namespace cutesms {
class RtmpUserCtrlMessage {
public:
    RtmpUserCtrlMessage(uint16_t type) { event_type_ = type; }

protected:
    uint16_t event_type_;
};

}  // namespace cutesms