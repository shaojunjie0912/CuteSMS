#pragma once
#include "placeholder.h"
namespace cutesms {
class Session;
class StreamTypePlaceHolder : public PlaceHolder {
public:
    StreamTypePlaceHolder();
    virtual ~StreamTypePlaceHolder();

public:
    std::string get_val(StreamSession& session) final;
};
};  // namespace cutesms