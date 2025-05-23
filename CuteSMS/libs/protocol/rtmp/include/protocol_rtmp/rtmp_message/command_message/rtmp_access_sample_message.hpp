#pragma once

#include <protocol_rtmp/rtmp_define.hpp>

#include "../../amf0/amf0_inc.hpp"


namespace cutesms {
class RtmpAccessSampleMessage {
    friend class RtmpSession;

public:
    RtmpAccessSampleMessage(bool video = true, bool audio = true);

public:
    int32_t decode(std::shared_ptr<RtmpMessage> rtmp_msg);
    std::shared_ptr<RtmpMessage> encode() const;

private:
    Amf0String command_name_;
    Amf0Boolean audio_;
    Amf0Boolean video_;
};

}  // namespace cutesms