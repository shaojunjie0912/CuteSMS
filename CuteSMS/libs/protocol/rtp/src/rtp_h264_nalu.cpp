#include <protocol_rtp/rtp_h264_nalu.h>

namespace cutesms {
bool RtpH264NALU::is_last_nalu() {
    auto it = rtp_pkts_.cbegin();
    if (it != rtp_pkts_.cend()) {
        return it->second->get_header().marker == 1;
    }
    return false;
}

uint16_t RtpH264NALU::get_first_seqno() {
    auto it = rtp_pkts_.begin();
    if (it != rtp_pkts_.end()) {
        return it->second->get_timestamp();
    }
    return 0;
}

uint16_t RtpH264NALU::get_last_seqno() {
    auto it = rtp_pkts_.cbegin();
    if (it != rtp_pkts_.cend()) {
        return it->second->get_timestamp();
    }
    return 0;
}
}  // namespace cutesms