#include <base/utils/utils.h>

#include <iostream>
#include <protocol_sdp/session-level/protocol_version.hpp>
#include <sstream>


namespace cutesms {
std::string ProtocolVersion::prefix = "v=";

bool ProtocolVersion::parse(const std::string& line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    std::string sversion = line.substr(prefix.size(), end_pos - prefix.size());
    try {
        version = std::stoi(sversion);
    } catch (std::exception& e) {
        return false;
    }

    return true;
}

void ProtocolVersion::set_version(int v) { version = v; }

int ProtocolVersion::get_version() { return version; }

std::string ProtocolVersion::to_string() const {
    std::ostringstream oss;
    oss << prefix << std::to_string(version) << std::endl;
    return oss.str();
}
}  // namespace cutesms