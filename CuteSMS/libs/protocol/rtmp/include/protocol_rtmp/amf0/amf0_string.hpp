#pragma once
#include <netinet/in.h>
#include <string.h>

#include <iostream>
#include <string>

#include "amf0_def.hpp"

namespace cutesms {
class Amf0String : public Amf0Data {
public:
    using value_type = std::string;
    static const AMF0_MARKER_TYPE marker = STRING_MARKER;
    Amf0String() : Amf0Data(STRING_MARKER) {}
    virtual ~Amf0String() {}

    int32_t decode(const uint8_t *data, size_t len) {
        // read marker
        uint8_t *p = (uint8_t *)data;
        if (len < 1) {
            return -1;
        }

        auto marker = *p;
        if (marker != STRING_MARKER) {
            return -2;
        }
        len--;
        p++;

        if (len < 2) {
            return -3;
        }

        uint16_t string_len = 0;
        string_len = ntohs(*(uint16_t *)p);  // UTF-8字符串长度
        p += 2;
        len -= 2;
        // read data
        if (len < string_len) {
            return -4;
        }
        value_.assign((const char *)p, string_len);  // UTF-8字符串内容
        p += string_len;
        len -= string_len;
        return p - (uint8_t *)data;
    }

    int32_t encode(uint8_t *buf, size_t len) const {
        uint8_t *data = buf;
        if (len < 1) {
            return 0;
        }
        // marker
        *data = (uint8_t)STRING_MARKER;
        data++;
        len--;
        // len
        if (len < 2) {
            return 0;
        }
        *((uint16_t *)data) = htons(value_.size());
        data += 2;
        len -= 2;
        if (len < value_.size()) {
            return 0;
        }
        // data
        memcpy(data, value_.data(), value_.size());
        data += value_.size();
        len -= value_.size();
        return data - buf;
    }

    const std::string &get_value() const { return value_; }

    void set_value(const std::string &s) { value_ = s; }

    size_t size() const { return 1 + 2 + value_.size(); }

public:
    std::string value_;
};

}  // namespace cutesms