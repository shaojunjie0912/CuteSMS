#pragma once
#include <memory>
namespace cutesms {
class WebSocketPacket {
public:
    typedef enum {
        CONTINUATION = 0x0,
        TEXT = 0x1,
        BINARY = 0x2,
        RSV3 = 0x3,
        RSV4 = 0x4,
        RSV5 = 0x5,
        RSV6 = 0x6,
        RSV7 = 0x7,
        CLOSE = 0x8,
        PING = 0x9,
        PONG = 0xA,
        CONTROL_RSVB = 0xB,
        CONTROL_RSVC = 0xC,
        CONTROL_RSVD = 0xD,
        CONTROL_RSVE = 0xE,
        CONTROL_RSVF = 0xF
    } OpCode;

    WebSocketPacket();
    virtual ~WebSocketPacket();

    int32_t decode(const char *data, int32_t len);
    int32_t encode(char *data, int32_t len);
    int32_t encode_header(char *data, int32_t len);
    static int32_t encode_header(char *data, int32_t len, OpCode code, bool fin, bool mask_flag,
                                 uint32_t mask_key, int32_t payload_len);
    int32_t header_size(int32_t payload_size);
    int32_t size();

    void set_opcode(OpCode opcode);
    OpCode get_opcode() { return opcode_; }
    void set_masking_key(uint32_t k);
    void set_payload(std::unique_ptr<char[]> payload, int32_t payload_len);
    std::string_view get_payload();

private:
    bool fin_ = false;
    OpCode opcode_;
    bool mask_ = false;
    int32_t payload_len_ = 0;
    uint32_t masking_key_;
    std::unique_ptr<char[]> payload_;
};
}  // namespace cutesms