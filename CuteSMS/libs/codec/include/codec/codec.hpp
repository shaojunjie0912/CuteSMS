#pragma once

#include <json/json.h>

#include <string>

namespace cutesms {
enum CodecType {
    CODEC_H264 = 0,
    CODEC_HEVC = 1,
    CODEC_AAC = 2,
    CODEC_MP3 = 3,
    CODEC_AV1 = 4,
    CODEC_OPUS = 5,
    CODEC_G711_ALOW = 6,
    CODEC_G711_ULOW = 7,
};

class Codec {
public:
    Codec(CodecType type, const std::string& name) : codec_type_(type), codec_name_(name) {}

    virtual ~Codec() {}

    std::string& get_codec_name() { return codec_name_; }

    CodecType get_codec_type() { return codec_type_; }

    virtual bool is_ready() { return ready_; }

    void set_data_rate(uint32_t v) { data_rate_ = v; }

    uint32_t get_data_rate() { return data_rate_; }

    virtual Json::Value to_json() {
        Json::Value v;
        return v;
    }

protected:
    CodecType codec_type_;
    std::string codec_name_;

protected:
    bool ready_ = false;
    uint32_t data_rate_;
};

}  // namespace cutesms