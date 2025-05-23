#pragma once

#include <string>

namespace cutesms {

struct RtcpMux {
public:
    inline static std::string prefix{"a=rtcp-mux"};
    RtcpMux() = default;
    bool parse(const std::string &line);
    std::string to_string() const;
};

}  // namespace cutesms
