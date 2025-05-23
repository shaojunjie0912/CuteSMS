#pragma once
#include <stdint.h>

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cutesms {
class Utils {
public:
    static uint64_t get_rand64();
    static std::string get_rand_str(size_t len);
    static uint32_t get_crc32(uint8_t *buf, size_t len);
    static uint32_t calc_mpeg_ts_crc32(uint8_t *buf, size_t len);
    static std::string calc_hmac_sha256(const std::string &key, const std::string &msg);
    static std::string calc_hmac_sha1(const std::string &key, const std::string &msg);
    static std::string sha256(const std::string &msg);
    static std::string sha1(const std::string &msg);
    static std::string md5(const std::string &msg, size_t out_len = 32);
    static bool parse_url(const std::string &url, std::string &protocol, std::string &domain, uint16_t &port,
                          std::string &path, std::unordered_map<std::string, std::string> &params);
    static bool is_lan(const std::string &ip);
    static bool is_wan(const std::string &ip);
    static bool is_ip_address(const std::string &str);
    static bool encode_base64(const std::string &input, std::string &output);
    static bool decode_base64(const std::string &input, std::string &output);
    static bool bin_to_hex_str(const std::string &input, std::string &output, bool upper = false);
    static bool hex_str_to_bin(const std::string &input, std::string &output);
    static int64_t get_current_ms();
    static int64_t get_ntp_time();
    static std::string get_utc_time();
    static std::string get_bin_path();
    static bool aes_encrypt(const std::string &plaintext, const std::string &key, std::string &ciphertext);
    static bool aes_decrypt(const std::string &ciphertext, const std::string &key, std::string &plaintext);
};
};  // namespace cutesms