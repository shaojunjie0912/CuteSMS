#pragma once

#include <string>

namespace cutesms {

struct Control {
public:
    Control(const std::string& val) { val_ = val; }

    Control() = default;

    inline static std::string prefix{"a=control:"};

    bool parse(const std::string& line);

    const std::string get_val() const { return val_; }

    std::string to_string() const;

protected:
    std::string val_;
};

};  // namespace cutesms