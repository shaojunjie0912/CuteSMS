#pragma once
#include <string>

namespace cutesms {
struct Msid {
public:
    static std::string prefix;
    virtual bool parse(const std::string& line);

public:
    std::string msid;
    std::string appdata;
};
}  // namespace cutesms