#include "uri.hpp"

#include <sstream>

#include "base/utils/utils.h"

namespace cutesms {
std::string Uri::prefix = "u=";
bool Uri::parse(const std::string& line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    uri = line.substr(prefix.size(), end_pos - prefix.size());
    return true;
}

std::string Uri::to_string() const {
    std::ostringstream oss;
    oss << prefix << uri << std::endl;
    return oss.str();
}
}  // namespace cutesms