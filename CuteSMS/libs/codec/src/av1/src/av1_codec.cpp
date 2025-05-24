#include <base/utils/utils.h>
#include <spdlog/spdlog.h>

#include <boost/algorithm/string.hpp>
#include <codec_av1/av1_codec.hpp>
#include <iostream>
#include <protocol_sdp/media-level/media_sdp.hpp>

namespace cutesms {
// a=fmtp:98 profile-level-id=42A01E; packetization-mode=0;
//   sprop-parameter-sets=&lt;parameter sets data#0&gt;
std::shared_ptr<AV1Codec> AV1Codec::create_from_sdp(const MediaSdp& media_sdp, const Payload& payload) {
    ((void)media_sdp);
    ((void)payload);
    std::shared_ptr<AV1Codec> codec = std::make_shared<AV1Codec>();
    return codec;
}

std::shared_ptr<AV1Codec> AV1Codec::create_from_av1_param(AV1SequenceParameters& av1_param) {
    ((void)av1_param);
    std::shared_ptr<AV1Codec> codec = std::make_shared<AV1Codec>();
    return codec;
}

AV1SequenceParameters& AV1Codec::get_av1_param() { return avc_param_; }

bool AV1Codec::gen_av1_param() { return true; }
}  // namespace cutesms