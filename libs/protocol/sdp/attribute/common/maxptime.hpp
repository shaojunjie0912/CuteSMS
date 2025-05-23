#pragma once
#include <stdint.h>

#include <string>

// a=maxptime:<maximum packet time>

//     This gives the maximum amount of media that can be encapsulated
//     in each packet, expressed as time in milliseconds.  The time
//     SHALL be calculated as the sum of the time the media present in
//     the packet represents.  For frame-based codecs, the time SHOULD
//     be an integer multiple of the frame size.  This attribute is
//     probably only meaningful for audio data, but may be used with
//     other media types if it makes sense.  It is a media-level
//     attribute, and it is not dependent on charset.  Note that this
//     attribute was introduced after RFC 2327, and non-updated
//     implementations will ignore this attribute.
namespace cutesms {
struct MaxPTimeAttr {
public:
    inline static std::string prefix{"a=maxptime:"};
    bool parse(const std::string &line);
    uint32_t get_max_packet_time() const { return max_packet_time; }

    void set_max_packet_time(uint32_t val) { max_packet_time = val; }

    std::string to_string() const;

protected:
    uint32_t max_packet_time;
};
};  // namespace cutesms