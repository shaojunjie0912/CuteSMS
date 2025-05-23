#pragma once
#include <memory>
#include <vector>

#include "box.h"

namespace cutesms {
class NetBuffer;
class HvccBox : public Box {
public:
    HvccBox();
    virtual ~HvccBox() = default;

    int64_t size() override;
    int64_t encode(NetBuffer& buf) override;
    int64_t decode(NetBuffer& buf) override;

protected:
    std::string hevc_config_;
};
}  // namespace cutesms