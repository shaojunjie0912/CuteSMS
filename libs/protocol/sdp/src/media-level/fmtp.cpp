#include <base/utils/utils.h>
#include <protocol_sdp/media-level/fmtp.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <sstream>

namespace cutesms {

bool Fmtp::parse(const std::string &line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    std::string valid_string = line.substr(prefix.size(), end_pos - prefix.size());
    std::vector<std::string> vs;
    std::string::size_type space_pos;
    space_pos = valid_string.find(" ");
    if (space_pos == std::string::npos) {
        return false;
    }

    std::string pt_str = valid_string.substr(0, space_pos);
    pt_ = std::atoi(pt_str.data());

    std::string param_str = valid_string.substr(space_pos + 1);

    std::vector<std::string> vs_params;
    boost::split(vs_params, param_str, boost::is_any_of(";"));

    for (size_t i = 0; i < vs_params.size(); i++) {
        std::string str = vs_params[i];
        boost::algorithm::trim(str);
        auto pos = str.find("=");
        if (pos == std::string::npos) {
            return false;
        }

        std::string k = str.substr(0, pos);
        std::string v = str.substr(pos + 1);

        fmt_params_[k] = v;
    }

    return true;
}

std::string Fmtp::to_string() const {
    std::ostringstream oss;
    std::vector<std::string> params;
    for (auto &kv : fmt_params_) {
        params.push_back(kv.first + "=" + kv.second);
    }

    oss << prefix << pt_ << " " << boost::join(params, "; ") << std::endl;
    return oss.str();
}

void Fmtp::add_param(const std::string &k, const std::string &v) { fmt_params_[k] = v; }
}  // namespace cutesms