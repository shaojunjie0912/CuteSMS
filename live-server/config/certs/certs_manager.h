#pragma once
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "openssl/ssl.h"


namespace cutesms {
class Config;
class CertManager {
public:
    CertManager(Config& top_conf);
    virtual ~CertManager();

    void start();
    int32_t add_cert(const std::string& domain, const std::string& key_file, const std::string& cert_file);
    std::shared_ptr<SSL_CTX> get_cert_ctx(const std::string& domain);
    void stop();

private:
    Config& top_conf_;
    std::shared_mutex ssl_ctxs_lck_;
    std::unordered_map<std::string, std::shared_ptr<SSL_CTX>> ssl_ctxs_;
    std::unordered_map<std::string, std::pair<std::string, std::string>> key_cert_files_;
    std::unordered_map<std::string, std::time_t> file_write_time_;
    std::shared_ptr<SSL_CTX> default_ctx_;
};
};  // namespace cutesms