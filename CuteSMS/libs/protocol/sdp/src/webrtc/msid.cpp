#include <base/utils/utils.h>

#include <boost/algorithm/string.hpp>
#include <protocol_sdp/webrtc/msid.hpp>

namespace cutesms {
std::string Msid::prefix = "a=msid:";
bool Msid::parse(const std::string& line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    std::string valid_string = line.substr(prefix.size(), end_pos - prefix.size());
    std::vector<std::string> vs;
    boost::split(vs, valid_string, boost::is_any_of(" "));
    if (vs.size() != 2) {
        return false;
    }

    msid = vs[0];
    appdata = vs[1];
    return true;
}
}  // namespace cutesms