#include <base/utils/utils.h>
#include <protocol_sdp/attribute/common/rtpmap.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <sstream>


namespace cutesms {
// a=rtpmap:<payload type> <encoding name>/<clock rate> [/<encoding
//   parameters>]
bool Rtpmap::parse(const std::string& line) {
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

    payload_type = std::atoi(vs[0].c_str());
    std::vector<std::string> tmp;
    boost::split(tmp, vs[1], boost::is_any_of("/"));
    if (tmp.size() < 2) {
        return false;
    }
    encoding_name = tmp[0];
    clock_rate = std::atoi(tmp[1].c_str());
    for (size_t i = 2; i < tmp.size(); i++) {
        encoding_params.emplace_back(tmp[i]);
    }
    return true;
}

std::string Rtpmap::to_string() const {
    std::ostringstream oss;
    oss << prefix << std::to_string(payload_type) << " " << encoding_name << "/" << clock_rate;
    if (encoding_params.size() > 0) {
        oss << boost::join(encoding_params, "/");
    }
    oss << std::endl;
    return oss.str();
}
}  // namespace cutesms