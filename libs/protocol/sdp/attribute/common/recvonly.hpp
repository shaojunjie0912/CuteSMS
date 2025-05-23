#pragma once
#include <string>
#include <vector>

namespace cutesms {
struct RecvOnlyAttr {
public:
    inline static std::string prefix{"a=recvonly"};
    bool parse(const std::string &line);
    std::string to_string() const;
};
};  // namespace cutesms