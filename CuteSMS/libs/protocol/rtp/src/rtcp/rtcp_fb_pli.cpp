#include <protocol_rtp/rtcp/rtcp_fb_pli.h>

namespace cutesms {

RtcpFbPli::RtcpFbPli() {
    header_.version = 2;
    header_.pt = PT_PSFB;
    header_.fmt = FMT_PLI;
    header_.length = 2;
}
}  // namespace cutesms