#pragma once

#include <memory>

#include "rtmp_user_ctrl_message.hpp"


namespace cutesms {
class RtmpStreamBeginMessage : public RtmpUserCtrlMessage {
public:
    RtmpStreamBeginMessage(uint32_t stream_id);
    int32_t decode(std::shared_ptr<RtmpMessage> rtmp_msg);
    std::shared_ptr<RtmpMessage> encode() const;

private:
    uint32_t stream_id_ = 0;
};
}  // namespace cutesms