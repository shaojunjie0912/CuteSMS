#include <base/utils/utils.h>
#include <protocol_sdp/ice/ice_pwd.h>

#include <sstream>

namespace cutesms {

bool IcePwd::parse(const std::string& line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    pwd_ = line.substr(prefix.size(), end_pos - prefix.size());
    return true;
}

std::string IcePwd::to_string() const {
    std::ostringstream oss;
    oss << prefix << pwd_ << std::endl;
    return oss.str();
}
}  // namespace cutesms