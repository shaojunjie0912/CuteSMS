#pragma once
#include <memory>
#include <string_view>

namespace cutesms {
class Box;
class NetBuffer;

class MP4BoxFactory {
public:
    MP4BoxFactory();
    virtual ~MP4BoxFactory() = default;

public:
    static std::pair<std::shared_ptr<Box>, int64_t> decode_box(NetBuffer& buf);
};
};  // namespace cutesms