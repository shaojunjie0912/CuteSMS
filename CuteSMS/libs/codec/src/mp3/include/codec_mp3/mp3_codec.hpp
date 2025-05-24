#pragma once
#include <memory>

#include "../../../include/codec/codec.hpp"

namespace cutesms {
class MediaSdp;
class Payload;

class MP3Codec : public Codec {
public:
    MP3Codec() : Codec(CODEC_MP3, "MP3") { ready_ = true; }

    virtual ~MP3Codec() {}
};

}  // namespace cutesms