#include <protocol_ts/ts_psi.hpp>

namespace cutesms {
int32_t TsPayloadPSI::encode(uint8_t *data, int32_t len) {
    ((void)data);
    ((void)len);
    return 0;
}

int32_t TsPayloadPSI::decode(uint8_t *data, int32_t len) {
    ((void)data);
    ((void)len);
    return 0;
}

int32_t TsPayloadPSI::size() { return 0; }

}  // namespace cutesms