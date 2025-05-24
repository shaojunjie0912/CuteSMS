#pragma once

#include <protocol_rtp/rtp_aac_nalu.h>
#include <protocol_rtp/rtp_au.h>
#include <protocol_rtp/rtp_packet.h>

#include <map>
#include <memory>
#include <unordered_map>

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