#include "ice_options.h"

#include <base/utils/utils.h>

#include <sstream>

namespace cutesms {

bool IceOption::parse(const std::string& line) {
    std::string::size_type end_pos = line.rfind("\r");
    if (end_pos == std::string::npos) {
        end_pos = line.size() - 1;
    }
    option = line.substr(prefix.size(), end_pos - prefix.size());
    return true;
}

std::string IceOption::to_string() const {
    std::ostringstream oss;
    oss << prefix << option << std::endl;
    return oss.str();
}
}  // namespace cutesms