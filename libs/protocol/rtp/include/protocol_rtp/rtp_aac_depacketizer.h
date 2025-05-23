#pragma once
#include <map>
#include <memory>
#include <unordered_map>

#include "rtp_aac_nalu.h"
#include "rtp_au.h"
#include "rtp_packet.h"

namespace cutesms {
class RtpPacket;
class RtpAACDepacketizer {
public:
    RtpAACDepacketizer() {};
    virtual ~RtpAACDepacketizer() {};
    std::shared_ptr<RtpAACNALU> on_packet(std::shared_ptr<RtpPacket> pkt);

private:
    std::unordered_map<uint32_t, std::map<uint16_t, std::shared_ptr<RtpPacket>>> time_rtp_pkts_buf_;
};
}  // namespace cutesms