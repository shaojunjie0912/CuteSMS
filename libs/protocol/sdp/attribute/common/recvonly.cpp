#include "recvonly.hpp"

#include <sstream>

namespace cutesms {

bool RecvOnlyAttr::parse(const std::string &line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    return true;
}

std::string RecvOnlyAttr::to_string() const {
    std::ostringstream oss;
    oss << prefix << std::endl;
    return oss.str();
}
}  // namespace cutesms