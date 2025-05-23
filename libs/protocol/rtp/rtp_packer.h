/*
 * @Author: jbl19860422
 * @Date: 2023-12-28 23:56:13
 * @LastEditTime: 2023-12-29 13:40:40
 * @LastEditors: jbl19860422
 * @Description:
 * @FilePath: \cutesms\cutesms\protocol\rtp\rtp_packer.h
 * Copyright (c) 2023 by jbl19860422@gitee.com, All Rights Reserved.
 */
#pragma once
// c
#include <stdint.h>
// stl
#include <atomic>
#include <list>
#include <memory>
#include <mutex>
#include <string_view>
#include <vector>

#include "rtp_packet.h"


namespace cutesms {
class RtpPacker {
public:
    RtpPacker();
    virtual ~RtpPacker();
    std::vector<std::shared_ptr<RtpPacket>> pack(char *data, int32_t len, uint8_t pt, int ssrc, int64_t pts);
    virtual std::vector<std::shared_ptr<RtpPacket>> pack(const std::list<std::string_view> &nalus, uint8_t pt,
                                                         int ssrc, int64_t pts);

public:
    uint16_t get_sequence_num();
    std::atomic<uint16_t> rtp_seqnum_{0};
};

class H265RtpPacker : public RtpPacker {
public:
    H265RtpPacker();
    virtual ~H265RtpPacker();
    std::vector<std::shared_ptr<RtpPacket>> pack(const std::list<std::string_view> &nalus, uint8_t pt,
                                                 int ssrc, int64_t pts) override;
};
};  // namespace cutesms
