#include <protocol_rtp/h265_rtp_pkt_info.h>
#include <protocol_rtp/rtp_h265_depacketizer.h>

#include <string_view>


namespace cutesms {

std::shared_ptr<RtpH265NALU> RtpH265Depacketizer::on_packet(std::shared_ptr<RtpPacket> pkt) {
    H265RtpPktInfo pkt_info;
    if (pkt_info.parse(pkt->get_payload().data(), pkt->get_payload().size()) < 0) {
        return nullptr;
    }

    auto& pkts_map = time_rtp_pkts_buf_[pkt->get_timestamp()];
    pkts_map.insert(std::pair(pkt->get_seq_num(), pkt));
    if (pkt->get_header().marker == 1) {
        std::shared_ptr<RtpH265NALU> out_pkt = std::make_shared<RtpH265NALU>();
        out_pkt->set_rtp_pkts(pkts_map);
        time_rtp_pkts_buf_.erase(pkt->get_timestamp());
        return out_pkt;
    }
    return nullptr;
}
}  // namespace cutesms