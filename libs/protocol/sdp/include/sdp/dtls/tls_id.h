#pragma once
// https://tools.ietf.org/html/rfc4145#section-4
#include <string>
namespace cutesms {
struct TlsIdAttr {
public:
    inline static std::string prefix{"a=tls-id:"};
    bool parse(const std::string &line);
    std::string to_string() const;
    const std::string &get_id() const { return id; }

    void set_id(const std::string &val) { id = val; }

public:
    std::string id;
};
}  // namespace cutesms