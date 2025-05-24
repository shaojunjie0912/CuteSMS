#pragma once
#include "placeholder.h"
namespace cutesms {
class Session;
class StreamPlaceHolder : public PlaceHolder {
public:
    StreamPlaceHolder();
    virtual ~StreamPlaceHolder();

public:
    std::string get_val(StreamSession& session) final;
};
};  // namespace cutesms