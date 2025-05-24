/*
 * @Author: jbl19860422
 * @Date: 2022-11-04 21:17:47
 * @LastEditTime: 2023-07-22 18:11:09
 * @LastEditors: jbl19860422
 * @Description:
 * @FilePath: \cutesms\cutesms\log\log.h
 * Copyright (c) 2023 by jbl19860422@gitee.com, All Rights Reserved.
 */
#pragma once
#include "spdlog/spdlog.h"
namespace cutesms {
class Log {
public:
    Log() {}

    virtual ~Log() {}

    static spdlog::logger* get_core_logger() { return ptr_core_logger_; }

    static spdlog::logger* get_hls_logger() { return ptr_hls_logger_; }

public:
    static void init(bool debug);

private:
    static std::shared_ptr<spdlog::logger> core_logger_;
    static std::shared_ptr<spdlog::logger> hls_logger_;
    static spdlog::logger* ptr_core_logger_;
    static spdlog::logger* ptr_hls_logger_;
};

#define CORE_TRACE(...) cutesms::Log::get_core_logger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...) cutesms::Log::get_core_logger()->debug(__VA_ARGS__)
#define CORE_INFO(...) cutesms::Log::get_core_logger()->info(__VA_ARGS__)
#define CORE_WARN(...) cutesms::Log::get_core_logger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) cutesms::Log::get_core_logger()->error(__VA_ARGS__)
#define CORE_FLUSH() cutesms::Log::get_core_logger()->flush()

#define APP_TRACE(APP_PTR, ...) APP_PTR->get_logger()->trace(__VA_ARGS__)
#define APP_DEBUG(APP_PTR, ...) APP_PTR->get_logger()->debug(__VA_ARGS__)
#define APP_INFO(APP_PTR, ...) APP_PTR->get_logger()->info(__VA_ARGS__)
#define APP_WARN(APP_PTR, ...) APP_PTR->get_logger()->warn(__VA_ARGS__)
#define APP_ERROR(APP_PTR, ...) APP_PTR->get_logger()->error(__VA_ARGS__)

#define HLS_TRACE(...) cutesms::Log::get_hls_logger()->trace(__VA_ARGS__)
#define HLS_DEBUG(...) cutesms::Log::get_hls_logger()->debug(__VA_ARGS__)
#define HLS_INFO(...) cutesms::Log::get_hls_logger()->info(__VA_ARGS__)
#define HLS_WARN(...) cutesms::Log::get_hls_logger()->warn(__VA_ARGS__)
#define HLS_ERROR(...) cutesms::Log::get_hls_logger()->error(__VA_ARGS__)
#define HLS_FLUSH() cutesms::Log::get_hls_logger()->flush()

};  // namespace cutesms