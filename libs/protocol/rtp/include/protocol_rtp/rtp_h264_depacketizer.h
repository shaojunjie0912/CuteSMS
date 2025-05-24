#pragma once

#include <protocol_rtp/rtp_h264_nalu.h>
#include <protocol_rtp/rtp_h264_packet.h>
#include <protocol_rtp/rtp_h264_rtp_pkt_info.h>

#include <map>
#include <memory>
#include <unordered_map>

// 参考算法：https://blog.csdn.net/u010178611/article/details/82625891
namespace cutesms {
class RtpH264Depacketizer {
public:
    RtpH264Depacketizer() {};
    virtual ~RtpH264Depacketizer() {};
    std::shared_ptr<RtpH264NALU> on_packet(std::shared_ptr<RtpPacket> pkt);

private:
    std::unordered_map<uint32_t, std::map<uint16_t, std::shared_ptr<RtpPacket>>> time_rtp_pkts_buf_;
};
}  // namespace cutesms