#pragma once
#include <map>
#include <memory>
#include <unordered_map>

#include "h264_rtp_pkt_info.h"
#include "rtp_h265_nalu.h"
#include "rtp_h265_packet.h"

// 参考算法：https://blog.csdn.net/u010178611/article/details/82625891
namespace cutesms {
class RtpH265Depacketizer {
public:
    RtpH265Depacketizer() {};
    virtual ~RtpH265Depacketizer() {};
    std::shared_ptr<RtpH265NALU> on_packet(std::shared_ptr<RtpPacket> pkt);

private:
    std::unordered_map<uint32_t, std::map<uint16_t, std::shared_ptr<RtpPacket>>> time_rtp_pkts_buf_;
};
};  // namespace cutesms