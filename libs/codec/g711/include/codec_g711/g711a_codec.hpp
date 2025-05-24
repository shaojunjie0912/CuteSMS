#pragma once

#include "../../codec.hpp"

namespace cutesms {
class MediaSdp;
class Payload;

class G711ACodec : public Codec {
public:
    G711ACodec() : Codec(CODEC_G711_ALOW, "G711ALOW") {}

    virtual ~G711ACodec() {}
};

}  // namespace cutesms