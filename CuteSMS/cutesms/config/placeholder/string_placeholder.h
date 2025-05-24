#pragma once
#include "placeholder.h"
namespace cutesms {
class StreamSession;
class StringPlaceHolder : public PlaceHolder {
public:
    StringPlaceHolder(const std::string& v);
    virtual ~StringPlaceHolder();

public:
    std::string get_val(StreamSession& session) final;

private:
    std::string val_;
};
};  // namespace cutesms