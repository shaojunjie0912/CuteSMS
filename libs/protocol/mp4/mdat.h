#pragma once
#include <string_view>
#include <vector>

#include "box.h"

namespace cutesms {
class MdatBox : public Box {
public:
    MdatBox();
    virtual ~MdatBox();

public:
    std::vector<std::string_view> datas_;
};
};  // namespace cutesms