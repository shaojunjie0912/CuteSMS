#pragma once
#include <stdint.h>
namespace cutesms {
class MOpusEncoder {
public:
    MOpusEncoder();
    virtual ~MOpusEncoder();
    bool init(int32_t sample_rate, int32_t channels);
    int32_t encode(uint8_t *data_in, int32_t in_len, uint8_t *data_out, int32_t out_len);

private:
    void *handle_ = nullptr;
};
}  // namespace cutesms