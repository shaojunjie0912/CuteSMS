#pragma once
namespace cutesms {
struct StunPasswordAttr : public StunMsgAttr {
    StunPasswordAttr() : StunMsgAttr(STUN_ATTR_PASSWORD) {}

    std::string password;
};
};  // namespace cutesms