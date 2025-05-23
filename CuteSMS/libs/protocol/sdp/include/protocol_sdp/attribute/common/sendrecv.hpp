#pragma once
#include <string>
#include <string_view>
#include <vector>

// a=sendrecv

//     This specifies that the tools should be started in send and
//     receive mode.  This is necessary for interactive conferences
//     with tools that default to receive-only mode.  It can be either
//     a session or media-level attribute, and it is not dependent on
//     charset.

//     If none of the attributes "sendonly", "recvonly", "inactive",
//     and "sendrecv" is present, "sendrecv" SHOULD be assumed as the
//     default for sessions that are not of the conference type
//     "broadcast" or "H332" (see below).
namespace cutesms {

struct SendRecvAttr {
    inline static std::string prefix{"a=sendrecv"};
    bool parse(const std::string &line);
    std::string to_string() const;
};

}  // namespace cutesms