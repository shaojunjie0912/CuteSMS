#pragma once

#include "../../../include/codec/codec.hpp"

namespace cutesms {
class MediaSdp;
class Payload;

class G711UCodec : public Codec {
public:
    G711UCodec() : Codec(CODEC_G711_ULOW, "G711ULOW") {}

    virtual ~G711UCodec() {}
};

}  // namespace cutesms