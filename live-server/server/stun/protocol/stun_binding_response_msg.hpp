#pragma once
#include <memory>

#include "stun_define.hpp"
#include "stun_msg.h"

namespace cutesms {
struct StunBindingResponseMsg : public StunMsg {
public:
    StunBindingResponseMsg(StunMsg& stun_msg) {
        header.type = STUN_BINDING_RESPONSE;
        memcpy(header.transaction_id, stun_msg.header.transaction_id, 16);
    }
};
};  // namespace cutesms