#pragma once
#include <memory>
#include <vector>

#include "box.h"


namespace cutesms {
class NetBuffer;
class AvccBox : public Box {
public:
    AvccBox();
    virtual ~AvccBox() = default;

    int64_t size() override;
    int64_t encode(NetBuffer& buf) override;
    int64_t decode(NetBuffer& buf) override;

public:
    std::string avc_config_;
};
};  // namespace cutesms